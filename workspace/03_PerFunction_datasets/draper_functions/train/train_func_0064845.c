UTTohhmm(gdouble UT, gint * h, gint * m)
{
	if (UT < 0.0) {
		*h = -1.0;
		*m = -1.0;
	} else {
		*h = (gint) UT;
		*m = (gint) ((UT - (gdouble) (*h)) * 60.0 + 0.5);
		if (*m == 60) {


			*h += 1;
			*m = 0;
		}
	}

}
