copy_path_costsize(Plan *dest, Path *src)
{
	if (src)
	{
		dest->startup_cost = src->startup_cost;
		dest->total_cost = src->total_cost;
		dest->plan_rows = src->parent->rows;
		dest->plan_width = src->parent->width;
	}
	else
	{
		dest->startup_cost = 0;
		dest->total_cost = 0;
		dest->plan_rows = 0;
		dest->plan_width = 0;
	}
}
