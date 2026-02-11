do_hda_entry(const char *filename, void *symval, char *alias)
{
	DEF_FIELD(symval, hda_device_id, vendor_id);
	DEF_FIELD(symval, hda_device_id, rev_id);
	DEF_FIELD(symval, hda_device_id, api_version);

	strcpy(alias, "hdaudio:");
	ADD(alias, "v", vendor_id != 0, vendor_id);
	ADD(alias, "r", rev_id != 0, rev_id);
	ADD(alias, "a", api_version != 0, api_version);

	add_wildcard(alias);
	return 1;
}
