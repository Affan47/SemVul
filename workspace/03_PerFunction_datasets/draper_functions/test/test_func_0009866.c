add_hintdevice(struct ast_hint *hint, const char *devicelist)
{
	struct ast_str *str;
	char *parse;
	char *cur;
	struct ast_hintdevice *device;
	int devicelength;

	if (!hint || !devicelist) {

		return 0;
	}
	if (!(str = ast_str_thread_get(&hintdevice_data, 16))) {
		return -1;
	}
	ast_str_set(&str, 0, "%s", devicelist);
	parse = parse_hint_device(str);

	while ((cur = strsep(&parse, "&"))) {
		devicelength = strlen(cur);
		device = ao2_t_alloc(sizeof(*device) + devicelength, hintdevice_destroy,
			"allocating a hintdevice structure");
		if (!device) {
			return -1;
		}
		strcpy(device->hintdevice, cur);
		ao2_ref(hint, +1);
		device->hint = hint;
		ao2_t_link(hintdevices, device, "Linking device into hintdevice container.");
		ao2_t_ref(device, -1, "hintdevice is linked so we can unref");
	}

	return 0;
}
