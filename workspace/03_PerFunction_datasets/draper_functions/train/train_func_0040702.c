Filter(GPSWindow ps,uint8 ch) {
    ps->ascii85encode = (ps->ascii85encode<<8) | ch;
    if ( ++ps->ascii85n == 4 ) {
	int c5, c4, c3, c2, c1;
	uint32 val = ps->ascii85encode;
	if ( val==0 ) {
	    putc('z',ps->output_file);
	    ps->ascii85n = 0;
	    if ( ++ps->ascii85bytes_per_line >= 76 ) {
		putc('\n',ps->output_file);
		ps->ascii85bytes_per_line = 0;
	    }
	} else {
	    c5 = val%85; val /= 85;
	    c4 = val%85; val /= 85;
	    c3 = val%85; val /= 85;
	    c2 = val%85;
	    c1 = val/85;
	    fprintf(ps->output_file, "%c%c%c%c%c",
		    c1+'!', c2+'!', c3+'!', c4+'!', c5+'!' );
	    ps->ascii85encode = 0;
	    ps->ascii85n = 0;
	    if (( ps->ascii85bytes_per_line+=5) >= 80 ) {
		putc('\n',ps->output_file);
		ps->ascii85bytes_per_line = 0;
	    }
	}
    }
}
