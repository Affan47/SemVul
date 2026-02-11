pk_time_get_gradient (PkTimeItem *item1, PkTimeItem *item2)
{
	gfloat dy;
	gfloat dx;
	if (item1->time == item2->time)
		return 0;
	dy = (gfloat) (item1->percentage - item2->percentage);
	dx = (gfloat) (item1->time - item2->time);
	return dy/dx;
}
