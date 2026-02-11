color_embed(char *fg, char *bg)
{
    static char buf[(2 * RGBLEN) + 5], *p;

    p = buf;
    if(fg){
	if(sizeof(buf)-(p-buf) > 1){
	  *p++ = TAG_EMBED;
	  *p++ = TAG_FGCOLOR;
	}

	sstrncpy(&p, color_to_asciirgb(fg), sizeof(buf)-(p-buf));
    }

    if(bg){
	if(sizeof(buf)-(p-buf) > 1){
	  *p++ = TAG_EMBED;
	  *p++ = TAG_BGCOLOR;
	}

	sstrncpy(&p, color_to_asciirgb(bg), sizeof(buf)-(p-buf));
    }

    buf[sizeof(buf)-1] = '\0';

    return(buf);
}
