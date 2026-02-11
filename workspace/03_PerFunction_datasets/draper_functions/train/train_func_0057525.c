ao_self_read(struct cc_usb *cc, uint32_t address, uint32_t length)
{
	struct ao_hex_image	*image;
	int			pages;
	int			page;
	uint32_t		base = address & ~0xff;
	uint32_t		bound = (address + length + 0xff) & ~0xff;

	image = calloc(sizeof (struct ao_hex_image) + (bound - base), 1);
	image->address = base;
	image->length = bound - base;
	pages = image->length / 0x100;
	for (page = 0; page < pages; page++)
		ao_self_block_read(cc, image->address + page * 0x100, image->data + page * 0x100);
	return image;
}
