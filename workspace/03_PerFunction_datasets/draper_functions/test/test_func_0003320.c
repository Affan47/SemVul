ahd_setup_data_scb(struct ahd_softc *ahd, struct scb *scb)
{


	if ((ahd->flags & AHD_64BIT_ADDRESSING) != 0) {
		struct ahd_dma64_seg *sg;

		sg = (struct ahd_dma64_seg *)scb->sg_list;
		scb->hscb->dataptr = sg->addr;
		scb->hscb->datacnt = sg->len;
	} else {
		struct ahd_dma_seg *sg;
		uint32_t *dataptr_words;

		sg = (struct ahd_dma_seg *)scb->sg_list;
		dataptr_words = (uint32_t*)&scb->hscb->dataptr;
		dataptr_words[0] = sg->addr;
		dataptr_words[1] = 0;
		if ((ahd->flags & AHD_39BIT_ADDRESSING) != 0) {
			uint64_t high_addr;

			high_addr = ahd_le32toh(sg->len) & 0x7F000000;
			scb->hscb->dataptr |= ahd_htole64(high_addr << 8);
		}
		scb->hscb->datacnt = sg->len;
	}


	scb->hscb->sgptr = ahd_htole32(scb->sg_list_busaddr|SG_FULL_RESID);
}
