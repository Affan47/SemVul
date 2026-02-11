gpm_array_float_get_average (GpmArrayFloat *array)
{
	guint i;
	guint length;
	gfloat average = 0;

	length = array->len;
	for (i=0; i<length; i++)
		average += g_array_index (array, gfloat, i);
	return average / (gfloat) length;
}
