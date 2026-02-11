fbcon_set_font(struct vc_data *vc, struct console_font *font, unsigned flags)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	unsigned charcount = font->charcount;
	int w = font->width;
	int h = font->height;
	int size;
	int i, csum;
	u8 *new_data, *data = font->data;
	int pitch = (font->width+7) >> 3;


	if (charcount != 256 && charcount != 512)
		return -EINVAL;


	if (!(info->pixmap.blit_x & (1 << (font->width - 1))) ||
	    !(info->pixmap.blit_y & (1 << (font->height - 1))))
		return -EINVAL;


	if (fbcon_invalid_charcount(info, charcount))
		return -EINVAL;

	size = h * pitch * charcount;

	new_data = kmalloc(FONT_EXTRA_WORDS * sizeof(int) + size, GFP_USER);

	if (!new_data)
		return -ENOMEM;

	new_data += FONT_EXTRA_WORDS * sizeof(int);
	FNTSIZE(new_data) = size;
	FNTCHARCNT(new_data) = charcount;
	REFCOUNT(new_data) = 0;
	for (i=0; i< charcount; i++) {
		memcpy(new_data + i*h*pitch, data +  i*32*pitch, h*pitch);
	}


	csum = crc32(0, new_data, size);

	FNTSUM(new_data) = csum;

	for (i = first_fb_vc; i <= last_fb_vc; i++) {
		struct vc_data *tmp = vc_cons[i].d;

		if (fb_display[i].userfont &&
		    fb_display[i].fontdata &&
		    FNTSUM(fb_display[i].fontdata) == csum &&
		    FNTSIZE(fb_display[i].fontdata) == size &&
		    tmp->vc_font.width == w &&
		    !memcmp(fb_display[i].fontdata, new_data, size)) {
			kfree(new_data - FONT_EXTRA_WORDS * sizeof(int));
			new_data = (u8 *)fb_display[i].fontdata;
			break;
		}
	}
	return fbcon_do_set_font(vc, font->width, font->height, new_data, 1);
}
