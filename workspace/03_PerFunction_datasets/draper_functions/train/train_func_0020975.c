GL_ResampleTexture (byte *in, int inwidth, int inheight, byte *out, int outwidth, int outheight)
{
	int		i, j;
	byte	*inrow, *inrow2;
	unsigned	frac, fracstep;
	unsigned	p1[1024], p2[1024];
	byte		*pix1, *pix2, *pix3, *pix4;

	fracstep = inwidth*0x10000/outwidth;

	frac = fracstep>>2;
	for (i=0 ; i<outwidth ; i++)
	{
		p1[i] = 4*(frac>>16);
		frac += fracstep;
	}
	frac = 3*(fracstep>>2);
	for (i=0 ; i<outwidth ; i++)
	{
		p2[i] = 4*(frac>>16);
		frac += fracstep;
	}

	for (i=0 ; i<outheight ; i++, out += outwidth*4)
	{
		inrow = in + 4*inwidth*(int)((i+0.25)*inheight/outheight);
		inrow2 = in + 4*inwidth*(int)((i+0.75)*inheight/outheight);
		frac = fracstep >> 1;
		for (j=0 ; j<outwidth ; j++)
		{
			pix1 = inrow + p1[j];
			pix2 = inrow + p2[j];
			pix3 = inrow2 + p1[j];
			pix4 = inrow2 + p2[j];
			*(out+4*j+0) = (pix1[0] + pix2[0] + pix3[0] + pix4[0])>>2;
			*(out+4*j+1) = (pix1[1] + pix2[1] + pix3[1] + pix4[1])>>2;
			*(out+4*j+2) = (pix1[2] + pix2[2] + pix3[2] + pix4[2])>>2;
			*(out+4*j+3) = (pix1[3] + pix2[3] + pix3[3] + pix4[3])>>2;
		}
	}
}
