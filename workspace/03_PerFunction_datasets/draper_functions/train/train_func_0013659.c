g_elliptical_arc(double rx, double ry, double t1, double t2, double cx, double cy, int arrow) {
	g_flush();
	GLEPoint orig(cx, cy);
	GLECore* core = g_get_core();
	if (core->isComputingLength()) {
		GLEEllipseArc arc(orig, rx, ry, t1*GLE_PI/180, t2*GLE_PI/180);
		core->addToLength(fabs(arc.getDist(arc.getT0(), arc.getT1())));
	}
	GLEWithoutUpdates noUpdates;
	if (arrow != 0) {
		GLEEllipseArc ellipse(orig, rx, ry, t1*GLE_PI/180, t2*GLE_PI/180);
		GLECurvedArrowHead head_start(&ellipse);
		GLECurvedArrowHead head_end(&ellipse);
		if (arrow == 1 || arrow == 3) g_init_arrow_head(&head_start, true);
		if (arrow == 2 || arrow == 3) g_init_arrow_head(&head_end, false);
		g_update_arc_bounds_for_arrow_heads(&head_start, &head_end, &t1, &t2);
		g.dev->elliptical_arc(rx, ry, t1, t2, cx, cy);
		head_start.computeAndDraw();
		head_end.computeAndDraw();
	} else {
		g.dev->elliptical_arc(rx, ry, t1, t2, cx, cy);
	}
	g.curx = cx; g.cury = cy;
}
