processYUVImage(imageStruct &image)
{
	t_atom out[4];
	unsigned int datasize = (image.xsize * image.ysize) >> 1;
	unsigned char *base = image.data;

	unsigned long sum[4] = {0,0,0,0};

	for (unsigned int i = 0; i != datasize; ++i)
	{
		for(int j = 0; j!= 4; ++j)
		{
			sum[j]  += base[j];
		}
		base += 4;
	}


        t_float y = (t_float)(sum[chY0]+sum[chY1]) / (t_float)(2*datasize) - 16;
        t_float u = (t_float) sum[chU] / (t_float)(datasize) - 128;
        t_float v = (t_float) sum[chV] / (t_float)(datasize) - 128;

        t_float r = FLOAT_CLAMP((t_float)(0.00456621*y             +0.00625893*v));
        t_float g = FLOAT_CLAMP((t_float)(0.00456621*y-0.00153632*u-0.00318811*v));
        t_float b = FLOAT_CLAMP((t_float)(0.00456621*y+0.00791071*u             ));

	SETFLOAT(out,   r);
	SETFLOAT(out+1, g);
        SETFLOAT(out+2, b);
	SETFLOAT(out+3, 1.0);

	outlet_list(m_list, 0, 4, out);

}
