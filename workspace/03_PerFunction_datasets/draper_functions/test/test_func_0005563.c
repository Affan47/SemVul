ch_flash_md_pos_to_text (ChFlashMdPos pos)
{
	if (pos == CH_FLASH_MD_POS_UNKNOWN)
		return "unknown";
	if (pos == CH_FLASH_MD_POS_UPDATES)
		return "updates";
	if (pos == CH_FLASH_MD_POS_UPDATE)
		return "update";
	if (pos == CH_FLASH_MD_POS_VERSION)
		return "version";
	if (pos == CH_FLASH_MD_POS_STATE)
		return "state";
	if (pos == CH_FLASH_MD_POS_FILENAME)
		return "filename";
	if (pos == CH_FLASH_MD_POS_CHECKSUM)
		return "checksum";
	if (pos == CH_FLASH_MD_POS_CHANGELOG)
		return "changelog";
	if (pos == CH_FLASH_MD_POS_INFO)
		return "info";
	if (pos == CH_FLASH_MD_POS_WARNING)
		return "warning";
	g_assert_not_reached ();
}
