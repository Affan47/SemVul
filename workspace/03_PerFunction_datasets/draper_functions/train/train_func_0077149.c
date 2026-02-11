yv12_yuy2_c(LONGLINEARGS)
{

    while (h--)
    {
	int i = w;
	while (--i >= 0)
	{
	    dest_y[i * 4] = src_y[i * 2];
	    dest_y[i * 4 + 2] = src_y[i * 2 + 1];
	    dest_y[i * 4 + ds_y] = src_y[i * 2 + ss_y];
	    dest_y[i * 4 + ds_y + 2] = src_y[i * 2 + ss_y + 1];

	    dest_y[i * 4 + 1] = dest_y[i * 4 + ds_y + 1] = src_cb[i];
	    dest_y[i * 4 + 3] = dest_y[i * 4 + ds_y + 3] = src_cr[i];
	}

	src_y += 2 * ss_y;
	src_cr += ss_cr;
	src_cb += ss_cb;

	dest_y += 2 * ds_y;
    }
}
