get_trim_dev_limit (void)
{
	char model[41];

	if (id[105] && id[105] != 0xffff)
		return id[105];
	extract_id_string(id + 27, 20, model);
	if (0 == strcmp(model, "OCZ VERTEX-LE"))
		return 8;
	if (0 == strcmp(model, "OCZ-VERTEX"))
		return 64;
	return 1;
}
