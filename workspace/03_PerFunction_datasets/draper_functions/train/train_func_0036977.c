is_pmbr_valid(legacy_mbr *mbr, sector_t total_sectors)
{
	uint32_t sz = 0;
	int i, part = 0, ret = 0;

	if (!mbr || le16_to_cpu(mbr->signature) != MSDOS_MBR_SIGNATURE)
		goto done;

	for (i = 0; i < 4; i++) {
		ret = pmbr_part_valid(&mbr->partition_record[i]);
		if (ret == GPT_MBR_PROTECTIVE) {
			part = i;


			goto check_hybrid;
		}
	}

	if (ret != GPT_MBR_PROTECTIVE)
		goto done;
check_hybrid:
	for (i = 0; i < 4; i++)
		if ((mbr->partition_record[i].os_type !=
			EFI_PMBR_OSTYPE_EFI_GPT) &&
		    (mbr->partition_record[i].os_type != 0x00))
			ret = GPT_MBR_HYBRID;


	if (ret == GPT_MBR_PROTECTIVE) {
		sz = le32_to_cpu(mbr->partition_record[part].size_in_lba);
		if (sz != (uint32_t) total_sectors - 1 && sz != 0xFFFFFFFF)
			pr_debug("GPT: mbr size in lba (%u) different than whole disk (%u).\n",
				 sz, min_t(uint32_t,
					   total_sectors - 1, 0xFFFFFFFF));
	}
done:
	return ret;
}
