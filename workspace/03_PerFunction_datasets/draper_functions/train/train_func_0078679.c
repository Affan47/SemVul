set_msg_colors_global(struct color_table *tbl,
			   unsigned int fg, unsigned int bg,
			   enum color_table_shadow shadow)
{
    struct color_table *cp = tbl + message_base_color;
    unsigned int i;
    unsigned int fga, bga;
    unsigned int fgh, bgh;
    unsigned int fg_idx, bg_idx;
    unsigned int fg_rgb, bg_rgb;

    static const unsigned int pc2rgb[8] =
	{ 0x000000, 0x0000ff, 0x00ff00, 0x00ffff, 0xff0000, 0xff00ff, 0xffff00,
	0xffffff
    };


    fga = fg & 0xff000000;
    fgh = ((fg >> 1) & 0xff000000) | 0x80000000;

    bga = bg & 0xff000000;
    bgh = ((bg >> 1) & 0xff000000) | 0x80000000;

    for (i = 0; i < 256; i++) {
	fg_idx = i & 15;
	bg_idx = i >> 4;

	fg_rgb = pc2rgb[fg_idx & 7] & fg;
	bg_rgb = pc2rgb[bg_idx & 7] & bg;

	if (fg_idx & 8) {

	    fg_rgb |= fgh;
	} else {
	    fg_rgb |= fga;
	}

	if (bg_idx == 0) {

	    bg_rgb = 0;
	} else if (bg_idx & 8) {
	    bg_rgb |= bgh;
	} else {
	    bg_rgb |= bga;
	}

	cp->argb_fg = fg_rgb;
	cp->argb_bg = bg_rgb;
	cp->shadow = shadow;
	cp++;
    }
}
