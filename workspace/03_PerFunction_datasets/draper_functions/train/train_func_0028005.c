show_palette_gradient()
{
    int i;
    double gray,r,g,b;

    ++c_token;
    if (sm_palette.colorMode != SMPAL_COLOR_MODE_GRADIENT) {
        fputs( "\tcolor mapping *not* done by defined gradient.\n", stderr );
	return;
    }

    for( i=0; i<sm_palette.gradient_num; ++i ) {
        gray = sm_palette.gradient[i].pos;
        r = sm_palette.gradient[i].col.r;
        g = sm_palette.gradient[i].col.g;
        b = sm_palette.gradient[i].col.b;
        fprintf(stderr,
 "%3i. gray=%0.4f, (r,g,b)=(%0.4f,%0.4f,%0.4f), #%02x%02x%02x = %3i %3i %3i\n",
		i, gray, r,g,b,
                (int)(255*r+.5),(int)(255*g+.5),(int)(255*b+.5),
                (int)(255*r+.5),(int)(255*g+.5),(int)(255*b+.5) );
	}
}
