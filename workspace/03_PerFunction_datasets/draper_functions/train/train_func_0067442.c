cavan_display_memory_xfer_dummy(struct cavan_display_device *display, struct cavan_display_memory *mem, bool read)
{
	byte *data;
	byte *p, *p_end;
	size_t line_size;
	int width;
	int right, bottom;

	right = mem->x + mem->width;
	if (right > display->xres)
	{
		right = display->xres;
	}

	if (mem->x < 0)
	{
		mem->x = 0;
	}

	bottom = mem->y + mem->height;
	if (bottom > display->yres)
	{
		bottom = display->yres;
	}

	if (mem->y < 0)
	{
		mem->y = 0;
	}

	if (mem->x >= right || mem->y >= bottom)
	{
		return 0;
	}

	mem->width = right - mem->x;
	mem->height = bottom - mem->y;

	width = mem->width * display->bpp_byte;
	line_size = display->bpp_byte * display->xres;

	p = (byte *) display->fb_base + mem->y * line_size + mem->x * display->bpp_byte;
	p_end = p + mem->height * line_size;

	data = mem->data;

	if (read)
	{
		while (p < p_end)
		{
			mem_copy(data, p, width);

			data += width;
			p += line_size;
		}
	}
	else
	{
		while (p < p_end)
		{
			mem_copy(p, data, width);

			data += width;
			p += line_size;
		}
	}

	return 0;
}
