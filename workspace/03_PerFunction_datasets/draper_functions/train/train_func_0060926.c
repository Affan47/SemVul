mb86290fb_imageblit8(u32 *cmd, u16 step, u16 dx, u16 dy,
				 u16 width, u16 height, u32 fgcolor,
				 u32 bgcolor, const struct fb_image *image,
				 struct fb_info *info)
{
	int i, j;
	unsigned const char *line, *ptr;
	u16 bytes;

	cmd[0] = (GDC_TYPE_DRAWBITMAPP << 24) |
	    (GDC_CMD_BLT_DRAW << 16) | (2 + (height * step));
	cmd[1] = (dy << 16) | dx;
	cmd[2] = (height << 16) | width;

	i = 0;
	line = ptr = image->data;
	bytes = image->width;

	while (i < height) {
		ptr = line;
		for (j = 0; j < step; j++) {
			cmd[3 + i * step + j] =
			    (((u32 *) (info->pseudo_palette))[*ptr]) & 0xffff;
			ptr++;
			cmd[3 + i * step + j] |=
			    ((((u32 *) (info->
					pseudo_palette))[*ptr]) & 0xffff) << 16;
			ptr++;
		}

		line += bytes;
		i++;
	}
}
