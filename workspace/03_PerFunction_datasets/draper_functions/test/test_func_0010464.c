sbc_dif_verify(struct se_cmd *cmd, sector_t start, unsigned int sectors,
	       unsigned int ei_lba, struct scatterlist *psg, int psg_off)
{
	struct se_device *dev = cmd->se_dev;
	struct t10_pi_tuple *sdt;
	struct scatterlist *dsg = cmd->t_data_sg;
	sector_t sector = start;
	void *daddr, *paddr;
	int i;
	sense_reason_t rc;
	int dsg_off = 0;
	unsigned int block_size = dev->dev_attrib.block_size;

	for (; psg && sector < start + sectors; psg = sg_next(psg)) {
		paddr = kmap_atomic(sg_page(psg)) + psg->offset;
		daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;

		for (i = psg_off; i < psg->length &&
				sector < start + sectors;
				i += sizeof(*sdt)) {
			__u16 crc;
			unsigned int avail;

			if (dsg_off >= dsg->length) {
				dsg_off -= dsg->length;
				kunmap_atomic(daddr - dsg->offset);
				dsg = sg_next(dsg);
				if (!dsg) {
					kunmap_atomic(paddr - psg->offset);
					return 0;
				}
				daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;
			}

			sdt = paddr + i;

			pr_debug("DIF READ sector: %llu guard_tag: 0x%04x"
				 " app_tag: 0x%04x ref_tag: %u\n",
				 (unsigned long long)sector, sdt->guard_tag,
				 sdt->app_tag, be32_to_cpu(sdt->ref_tag));

			if (sdt->app_tag == cpu_to_be16(0xffff)) {
				dsg_off += block_size;
				goto next;
			}

			avail = min(block_size, dsg->length - dsg_off);
			crc = crc_t10dif(daddr + dsg_off, avail);
			if (avail < block_size) {
				kunmap_atomic(daddr - dsg->offset);
				dsg = sg_next(dsg);
				if (!dsg) {
					kunmap_atomic(paddr - psg->offset);
					return 0;
				}
				daddr = kmap_atomic(sg_page(dsg)) + dsg->offset;
				dsg_off = block_size - avail;
				crc = crc_t10dif_update(crc, daddr, dsg_off);
			} else {
				dsg_off += block_size;
			}

			rc = sbc_dif_v1_verify(cmd, sdt, crc, sector, ei_lba);
			if (rc) {
				kunmap_atomic(daddr - dsg->offset);
				kunmap_atomic(paddr - psg->offset);
				cmd->bad_sector = sector;
				return rc;
			}
next:
			sector++;
			ei_lba++;
		}

		psg_off = 0;
		kunmap_atomic(daddr - dsg->offset);
		kunmap_atomic(paddr - psg->offset);
	}

	return 0;
}
