cmp_data_points (GObject *a, GObject *b)
{
	int ind_a = 0, ind_b = 0;

	g_object_get (a, "index", &ind_a, NULL);
	g_object_get (b, "index", &ind_b, NULL);

	if (ind_a < ind_b)
		return -1;
	else if (ind_a > ind_b)
		return 1;
	else return 0;
}
