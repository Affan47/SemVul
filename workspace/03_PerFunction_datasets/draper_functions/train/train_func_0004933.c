free_temp_point(vertex *p)
{
	Assert(p->flags & PF_TEMP_POINT);

	free_points[--free_point_num] = p;

	p->flags &= ~PF_TEMP_POINT;
}
