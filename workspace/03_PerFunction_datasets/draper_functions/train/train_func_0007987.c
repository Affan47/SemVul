gpm_array_float_remove_outliers (GpmArrayFloat *data, guint length, gfloat sigma)
{
	guint i;
	guint j;
	guint half_length;
	gfloat value;
	gfloat average;
	gfloat average_not_inc;
	gfloat average_square;
	gfloat biggest_difference;
	gfloat outlier_value;
	GpmArrayFloat *result;

	g_return_val_if_fail (length % 2 == 1, NULL);
	result = gpm_array_float_new (data->len);


	if (data->len == 0)
		goto out;

	half_length = (length - 1) / 2;


	for (i=0; i < half_length; i++)
		g_array_index (result, gfloat, i) = g_array_index (data, gfloat, i);
	for (i=data->len-half_length; i < data->len; i++)
		g_array_index (result, gfloat, i) = g_array_index (data, gfloat, i);


	for (i=half_length; i < data->len-half_length; i++) {
		average = 0;
		average_square = 0;


		for (j=i-half_length; j<i+half_length+1; j++) {
			value = g_array_index (data, gfloat, j);
			average += value;
			average_square += powfi (value, 2);
		}


		average /= length;
		average_square /= length;


		value = sqrtf (average_square - powfi (average, 2));


		if (value < sigma) {
			g_array_index (result, gfloat, i) = g_array_index (data, gfloat, i);
		} else {

			biggest_difference = 0;
			outlier_value = 0;
			for (j=i-half_length; j<i+half_length+1; j++) {
				value = fabs (g_array_index (data, gfloat, j) - average);
				if (value > biggest_difference) {
					biggest_difference = value;
					outlier_value = g_array_index (data, gfloat, j);
				}
			}
			average_not_inc = (average * length) - outlier_value;
			average_not_inc /= length - 1;
			g_array_index (result, gfloat, i) = average_not_inc;
		}
	}
out:
	return result;
}
