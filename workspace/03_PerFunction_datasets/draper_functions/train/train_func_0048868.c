dif_verify(struct sd_dif_tuple *sdt, const void *data,
		      sector_t sector, u32 ei_lba)
{
	__be16 csum = dif_compute_csum(data, scsi_debug_sector_size);

	if (sdt->guard_tag != csum) {
		pr_err("GUARD check failed on sector %lu rcvd 0x%04x, data 0x%04x\n",
			(unsigned long)sector,
			be16_to_cpu(sdt->guard_tag),
			be16_to_cpu(csum));
		return 0x01;
	}
	if (scsi_debug_dif == SD_DIF_TYPE1_PROTECTION &&
	    be32_to_cpu(sdt->ref_tag) != (sector & 0xffffffff)) {
		pr_err("REF check failed on sector %lu\n",
			(unsigned long)sector);
		return 0x03;
	}
	if (scsi_debug_dif == SD_DIF_TYPE2_PROTECTION &&
	    be32_to_cpu(sdt->ref_tag) != ei_lba) {
		pr_err("REF check failed on sector %lu\n",
			(unsigned long)sector);
		return 0x03;
	}
	return 0;
}
