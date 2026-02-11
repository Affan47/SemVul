tex_draw_accent_cmb(uchar **in, TexArgStrs* params, int *out, int *lout) {
	if (params->str4.length() != 0 && params->str3.length() != 0) {
		if (params->str3.length() == 1) {
			int accent;
			int ch = params->str3[0];
			texint(params->str4, &accent);
			GLECoreFont* cfont = set_tex_font(p_fnt);
			FontCompositeInfo* info = cfont->get_composite_char(ch, accent);
			if (info != NULL) {
				double w1 = cfont->getCharDataThrow(info->c1)->wx * p_hei;
				double w2 = cfont->getCharDataThrow(info->c2)->wx * p_hei;
				double dx1 = info->dx1 * p_hei;
				double dx2 = info->dx2 * p_hei;
				double dy1 = info->dy1 * p_hei;
				double dy2 = info->dy2 * p_hei;
				p_move(dx1, dy1);
				p_fntchar(p_fnt, info->c1);
				p_move(dx2-dx1-w1, dy2-dy1);
				p_fntchar(p_fnt, info->c2);
				p_move(w1-w2-dx2, -dy2);
			} else {
				if (ch == 'i') params->str3[0] = 0x10;
				if (ch == 'j') params->str3[0] = 0x11;
				tex_draw_accent(in, params, out, lout);
			}
		} else {
			tex_draw_accent(in, params, out, lout);
		}
	}
}
