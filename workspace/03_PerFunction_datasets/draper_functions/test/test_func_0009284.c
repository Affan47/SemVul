name_join(const char *n1, const char *n2, int marrow, double a1, double a2, double d1, double d2)  throw(ParserError) {
	GLEJustify j1, j2;
	GLEObjectRepresention* obj1 = name_to_object(n1, &j1);
	GLEObjectRepresention* obj2 = name_to_object(n2, &j2);
	if (j1 == GLEJustifyHorz || j1 == GLEJustifyVert) {
		GLEObjectRepresention* tmpo = obj1; obj1 = obj2; obj2 = tmpo;
		GLEJustify tmpj = j1; j1 = j2; j2 = tmpj;
		if (marrow==2) marrow = 1;
		else if (marrow==1) marrow = 2;
	}
	GLERectangle rect1, rect2;
	rect1.copy(obj1->getRectangle());
	rect2.copy(obj2->getRectangle());
	g_undev(&rect1);
	g_undev(&rect2);
	GLEPoint p1, p2;
	rect1.toPoint(j1, &p1);
	p2.set(p1);
	rect2.toPoint(j2, &p2);
	double sx = p1.getX();
	double sy = p1.getY();
	double ex = p2.getX();
	double ey = p2.getY();
	nm_adjust(j1, &sx, &sy, p2.getX(), p2.getY(), &rect1);
	nm_adjust(j2, &ex, &ey, p1.getX(), p1.getY(), &rect2);
	g_move(sx,sy);
	if (marrow==2) marrow = 1;
	else if (marrow==1) marrow = 2;
	g_arrowcurve(ex, ey, marrow, a1, a2, d1, d2);
}
