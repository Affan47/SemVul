dochar(int font, int cc) {
	read_psfont();
	if (font_get_encoding(font)>2) {
		my_char(font,cc);
		return;
	}
	if (d_ps_this_font!=font || d_ps_this_size!=g.fontsz) {
		if (g.fontsz<0.00001) {
			gprint("Font size is zero, error ********* \n");
			return;
		}
		char *s = font_getname(font);
		for (i=0;;i++) {
			if (psf[i].sname==NULL) break;
			dbg printf("font match  {%s} {%s} \n",s,psf[i].sname);
			if (str_i_equals(psf[i].sname,s)) break;
		}
		if (psf[i].sname==NULL) {
			my_char(font,cc);
			return;
		}
		d_ps_this_font = font;
		d_ps_this_size = g.fontsz;
		out() << g.fontsz << " /" << psf[i].lname << " f" << endl;
	}
	if (cc >= 256) {
		if (cc <= 420) {

			out() << "/" << ps_glyph_name_map[cc-256].name << " glyphshow" << endl;
		}
	} else {
		if (isalnum(cc) && cc < 127) {
			out() << "(" << (char)cc << ")";
		} else {
			char temp[50];
			sprintf(temp,"(\\%o)",cc);
			out() << temp;
		}
		if (g.inpath) {
			out() << " ps" << endl;
		} else {
			out() << " s" << endl;
		}
	}
}
