gpm_array_float_get (GpmArrayFloat *array, guint i)
{
	if (i >= array->len)
		g_error ("above index! (%i)", i);
	return g_array_index (array, gfloat, i);
}
