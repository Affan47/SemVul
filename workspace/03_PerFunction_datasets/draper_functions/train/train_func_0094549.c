print_label_list(VOID)
{
	boot_image_t *img, *dfl = global_config.default_image;

	if (dfl) Print(L"    %s\n", dfl->label);

	for (img = image_list; img; img = img->next) {
		if (img != dfl) Print(L"    %s\n", img->label);
	}
}
