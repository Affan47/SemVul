bttv_risc_packed(struct bttv *btv, struct btcx_riscmem *risc,
		 struct scatterlist *sglist,
		 unsigned int offset, unsigned int bpl,
		 unsigned int padding, unsigned int skip_lines,
		 unsigned int store_lines)
{
	u32 instructions,line,todo;
	struct scatterlist *sg;
	__le32 *rp;
	int rc;


	instructions  = skip_lines * 4;
	instructions += (1 + ((bpl + padding) * store_lines)
			 / PAGE_SIZE + store_lines) * 8;
	instructions += 2 * 8;
	if ((rc = btcx_riscmem_alloc(btv->c.pci,risc,instructions)) < 0)
		return rc;


	rp = risc->cpu;
	*(rp++) = cpu_to_le32(BT848_RISC_SYNC|BT848_FIFO_STATUS_FM1);
	*(rp++) = cpu_to_le32(0);

	while (skip_lines-- > 0) {
		*(rp++) = cpu_to_le32(BT848_RISC_SKIP | BT848_RISC_SOL |
				      BT848_RISC_EOL | bpl);
	}


	sg = sglist;
	for (line = 0; line < store_lines; line++) {
		if ((btv->opt_vcr_hack) &&
		    (line >= (store_lines - VCR_HACK_LINES)))
			continue;
		while (offset && offset >= sg_dma_len(sg)) {
			offset -= sg_dma_len(sg);
			sg = sg_next(sg);
		}
		if (bpl <= sg_dma_len(sg)-offset) {

			*(rp++)=cpu_to_le32(BT848_RISC_WRITE|BT848_RISC_SOL|
					    BT848_RISC_EOL|bpl);
			*(rp++)=cpu_to_le32(sg_dma_address(sg)+offset);
			offset+=bpl;
		} else {

			todo = bpl;
			*(rp++)=cpu_to_le32(BT848_RISC_WRITE|BT848_RISC_SOL|
					    (sg_dma_len(sg)-offset));
			*(rp++)=cpu_to_le32(sg_dma_address(sg)+offset);
			todo -= (sg_dma_len(sg)-offset);
			offset = 0;
			sg = sg_next(sg);
			while (todo > sg_dma_len(sg)) {
				*(rp++)=cpu_to_le32(BT848_RISC_WRITE|
						    sg_dma_len(sg));
				*(rp++)=cpu_to_le32(sg_dma_address(sg));
				todo -= sg_dma_len(sg);
				sg = sg_next(sg);
			}
			*(rp++)=cpu_to_le32(BT848_RISC_WRITE|BT848_RISC_EOL|
					    todo);
			*(rp++)=cpu_to_le32(sg_dma_address(sg));
			offset += todo;
		}
		offset += padding;
	}


	risc->jmp = rp;
	BUG_ON((risc->jmp - risc->cpu + 2) * sizeof(*risc->cpu) > risc->size);
	return 0;
}
