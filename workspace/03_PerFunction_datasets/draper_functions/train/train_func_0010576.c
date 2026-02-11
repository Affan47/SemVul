gpt_check_lba_sanity(struct fdisk_context *cxt, struct gpt_header *header)
{
	int ret = 0;
	uint64_t lu, fu, lastlba = last_lba(cxt);

	fu = le64_to_cpu(header->first_usable_lba);
	lu = le64_to_cpu(header->last_usable_lba);


	if (lu < fu) {
		DBG(LABEL, ul_debug("error: header last LBA is before first LBA"));
		goto done;
	}


	if (fu > lastlba || lu > lastlba) {
		DBG(LABEL, ul_debug("error: header LBAs are after the disk's last LBA"));
		goto done;
	}


	if (fu < GPT_PRIMARY_PARTITION_TABLE_LBA &&
	    GPT_PRIMARY_PARTITION_TABLE_LBA < lu) {
		DBG(LABEL, ul_debug("error: header outside of usable range"));
		goto done;
	}

	ret = 1;
done:
	return ret;
}
