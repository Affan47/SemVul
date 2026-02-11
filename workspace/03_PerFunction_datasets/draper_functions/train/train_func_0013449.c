rateconv(short *in,int isize, short **out, int *osize,
	     int in_samp_freq, int out_samp_freq)
{
    int insize = 0, outsize = 0, skirtlen;

    if (init_globs(in,isize,out,osize,in_samp_freq,out_samp_freq) == -1)
	return -1;

    make_coe();
    skirtlen = (g_firlen - 1) * (g_monoflag ? 1 : 2);
    zerofill(g_sin, skirtlen);
    do {
	insize = intimport(g_sin + skirtlen, INBUFFSIZE - skirtlen);
	if (insize < 0 || insize > INBUFFSIZE - skirtlen)
	    return ioerr();
	do {
	    outsize = filtering_on_buffers(g_sin, skirtlen + insize,
					   g_sout, OUTBUFFSIZE,
					   g_coep, g_firlen, g_up, g_down,
					   g_monoflag);
	    if (outsize != OUTBUFFSIZE) {
		transfer_int(g_sin + insize, g_sin, skirtlen);
		break;
	    }
	    if (intexport(g_sout, outsize) != outsize)
		return ioerr();
	} while (-1);
    } while (insize > 0);
    zerofill(g_sin + skirtlen, skirtlen);
    do {
	outsize = filtering_on_buffers(g_sin, skirtlen + skirtlen,
				       g_sout, OUTBUFFSIZE,
				       g_coep, g_firlen, g_up, g_down,
				       g_monoflag);
	if (intexport(g_sout, outsize) != outsize)
	    return ioerr();
    } while (outsize == OUTBUFFSIZE);

    delete g_coep;

    *osize = outpos;


    memmove(*out,*out+g_firlen/4,*osize*2);
    *osize -= g_firlen/4;

    return 0;

}
