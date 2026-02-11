BoxFillRoundRect(GWindow gw, GRect *r, int rr, Color color)
{
	int radius = rr <= (r->height+1)/2 ? (rr > 0 ? rr : 0) : (r->height+1)/2;
	int xend = r->x + r->width - 1;
	int yend = r->y + r->height - 1;
	int precalc = radius * 2 - 1;
	int i, xoff;

	GRect middle = {r->x, r->y + radius, r->width, r->height - 2 * radius};

    if (r->height <= 0)
return;

    for (i = 0; i < radius; i++)
	{
		xoff = radius - lrint(sqrt( (double)(i * (precalc - i)) ));
		GDrawDrawLine(gw, r->x + xoff, r->y + i, xend - xoff, r->y + i, color);
		GDrawDrawLine(gw, r->x + xoff, yend - i, xend - xoff, yend - i, color);
	}

	GDrawFillRect(gw, &middle, color);
}
