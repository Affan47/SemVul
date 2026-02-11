clip_pointxy(gdouble x,   gdouble y,
		       gdouble xg1, gdouble yg1,
		       gdouble xg2, gdouble yg2)
{
    return ((x >= xg1) && (x <= xg2) && (y >= yg1) && (y <= yg2));
}
