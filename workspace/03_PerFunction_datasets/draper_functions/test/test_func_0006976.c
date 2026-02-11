oct_division_check(struct octdata *data)
{
    if (data->points == NULL)
	return -1;
    if (data->n_points < KMAX)
	return 0;
    else
	return 1;
}
