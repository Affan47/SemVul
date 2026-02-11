pixbuf_copy_block_rotate(guchar *src, gint src_row_stride, gint x, gint y,
				     guchar *dest, gint dest_row_stride, gint w, gint h,
				     gint bytes_per_pixel, gboolean counter_clockwise)
{
	gint i, j;
	guchar *sp;
	guchar *dp;

	for (i = 0; i < h; i++)
		{
		sp = src + ((i + y) * src_row_stride) + (x * bytes_per_pixel);
		for (j = 0; j < w; j++)
			{
			if (counter_clockwise)
				{
				dp = dest + ((w - j - 1) * dest_row_stride) + (i * bytes_per_pixel);
				}
			else
				{
				dp = dest + (j * dest_row_stride) + ((h - i - 1) * bytes_per_pixel);
				}
			*(dp++) = *(sp++);
			*(dp++) = *(sp++);
			*(dp++) = *(sp++);
			if (bytes_per_pixel == 4) *(dp) = *(sp++);
			}
		}

}
