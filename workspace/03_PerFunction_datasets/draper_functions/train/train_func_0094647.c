rect(int relative, int filled, float cur_pensize, HPGL_Pt p)
{
	HPGL_Pt p1;

	if (relative) {
		p.x += p_last.x;
		p.y += p_last.y;
	}
	if (!filled) {
		p1.x = p_last.x;
		p1.y = p.y;
		Pen_action_to_tmpfile(DRAW_TO, &p1, scale_flag);
		p1.x = p.x;
		p1.y = p.y;
		Pen_action_to_tmpfile(DRAW_TO, &p1, scale_flag);
		p1.x = p.x;
		p1.y = p_last.y;
		Pen_action_to_tmpfile(DRAW_TO, &p1, scale_flag);
		p1.x = p_last.x;
		p1.y = p_last.y;
		Pen_action_to_tmpfile(DRAW_TO, &p1, scale_flag);
	} else {
		vertices = -1;
		HPGL_Pt_to_polygon(p_last);
		p1.x = p_last.x;
		p1.y = p.y;
		HPGL_Pt_to_polygon(p1);
		HPGL_Pt_to_polygon(p1);
		HPGL_Pt_to_polygon(p);
		HPGL_Pt_to_polygon(p);
		p1.x = p.x;
		p1.y = p_last.y;
		HPGL_Pt_to_polygon(p1);
		HPGL_Pt_to_polygon(p1);
		HPGL_Pt_to_polygon(p_last);
		if (hatchspace == 0.)
			hatchspace = cur_pensize;
		if (filltype < 3 && thickness > 0.)
			hatchspace = thickness;
		if (ac_flag == 0) {
			anchor.x = P1.x;
			anchor.y = P1.y;


		}
		fill(polygons, vertices, anchor, P2, scale_flag,
		     filltype, hatchspace, hatchangle);
	}
	Pen_action_to_tmpfile(MOVE_TO, &p_last, scale_flag);
}
