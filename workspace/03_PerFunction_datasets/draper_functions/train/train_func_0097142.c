exif_mnote_data_pentax_identify (const ExifData *ed, const ExifEntry *e)
{
	if ((e->size >= 8) && !memcmp (e->data, "AOC", 4)) {
		if (((e->data[4] == 'I') && (e->data[5] == 'I')) ||
		    ((e->data[4] == 'M') && (e->data[5] == 'M')))
			return pentaxV3;
		else

			return pentaxV2;
	}

	if ((e->size >= 8) && !memcmp (e->data, "QVC", 4))
		return casioV2;


	if ((e->size >= 2) && (e->data[0] == 0x00) && (e->data[1] == 0x1b))
		return pentaxV1;

	return 0;
}
