delete_firmware_description(struct firmware *f, __u16 i) {
	struct firmware_description* new_desc;

	if(f->nr_desc == 0 || i >= f->nr_desc) {
		return;
	}

	new_desc = malloc((f->nr_desc - 1) * sizeof(*new_desc));
	memcpy(new_desc, f->desc, i * sizeof(*f->desc));
	memcpy(new_desc + i, f->desc + i + 1, (f->nr_desc - i - 1) * sizeof(*f->desc));
	free(f->desc);
	f->desc = new_desc;
	--f->nr_desc;
}
