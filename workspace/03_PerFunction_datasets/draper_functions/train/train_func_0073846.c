ide_check_nien_quirk_list(ide_drive_t *drive)
{
	const char **list, *m = (char *)&drive->id[ATA_ID_PROD];

	for (list = nien_quirk_list; *list != NULL; list++)
		if (strstr(m, *list) != NULL) {
			drive->dev_flags |= IDE_DFLAG_NIEN_QUIRK;
			return;
		}
}
