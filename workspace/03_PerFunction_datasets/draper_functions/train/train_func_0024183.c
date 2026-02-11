outbuf_append(const char* buf, int n)
{
    if (outbuf_base+outbuf_total < outbuf_in+n) {


	if (outbuf_out > outbuf_base) {
	    int size = outbuf_in - outbuf_out;
	    char* p;

	    outbuf_in -= outbuf_out - outbuf_base;
	    p = outbuf_base;
	    while (size-- > 0) {
		*p++ = *outbuf_out++;
	    }
	    outbuf_out = outbuf_base;
	}


	if (outbuf_base+outbuf_total < outbuf_in+n) {
	    int size = outbuf_in - outbuf_out;
	    outbuf_total = size+n;
	    outbuf_base = realloc(outbuf_base, outbuf_total);
	    outbuf_out = outbuf_base;
	    outbuf_in = outbuf_base + size;
	}
    }


    memcpy(outbuf_in, buf, n);
    outbuf_in += n;
}
