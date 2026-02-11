yv12_bgr24_c(LONGLINEARGS)
{
    while (h--)
    {

	col* dest = (col*) dest_y;
        col* dest2 = (col*) (dest_y + ds_y);
        int i;
	for (i = 0; i < w; i++)
	{
	    yuv p;
	    p.Cr = src_cr[i];
	    p.Cb = src_cb[i];
	    p.Y = src_y[i * 2];
	    dest[i * 2] = p;
	    p.Y = src_y[i * 2 + 1];
	    dest[i * 2 + 1] = p;
	    p.Y = src_y[i * 2 + ss_y];
	    dest2[i * 2] = p;
	    p.Y = src_y[i * 2 + ss_y + 1];
	    dest2[i * 2 + 1] = p;
	}

	src_y += 2 * ss_y;
	src_cr += ss_cr;
	src_cb += ss_cb;

	dest_y += 2 * ds_y;
    }
}
