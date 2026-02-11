lines(int relative, FILE * hd)


{
	HPGL_Pt p;
	int numcmds = 0;
	int outside = 0;
	double p1x, p1y, p2x, p2y;

	for (;;) {
		if (read_float(&p.x, hd)) {
			if (numcmds > 0)
				return;
			if (pen_down && mv_flag && pen > 0 && pt.width[pen] < 0.35) {

				p.x = p_last.x + 0.01;
				p.y = p_last.y + 0.01;
				outside = 0;
				if (iwflag) {
					p1x =
					    P1.x + (p_last.x - S1.x) * Q.x;
					p1y =
					    P1.y + (p_last.y - S1.y) * Q.y;
					p2x = P1.x + (p.x - S1.x) * Q.x;
					p2y = P1.y + (p.y - S1.y) * Q.y;

					outside =
					    (DtClipLine
					     (C1.x, C1.y, C2.x, C2.y, &p1x,
					      &p1y, &p2x,
					      &p2y) == CLIP_NODRAW);
				}
				if (!outside) {
					Pen_action_to_tmpfile(MOVE_TO, &p,
							      scale_flag);
					Pen_action_to_tmpfile(DRAW_TO,
							      &p_last,
							      scale_flag);
				}
			}
			return;
		}

		if (read_float(&p.y, hd))
			par_err_exit(2, PA, hd);
		line(relative, p);
		numcmds++;
	}
}
