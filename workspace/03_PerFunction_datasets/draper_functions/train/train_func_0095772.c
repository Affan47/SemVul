string_to_geometricpoint (const GValue *src, GValue *dest)
{
	GdaGeometricPoint *point;
	const gchar *as_string;

	g_return_if_fail (G_VALUE_HOLDS_STRING (src) &&
			  GDA_VALUE_HOLDS_GEOMETRIC_POINT (dest));

	as_string = g_value_get_string (src);
	point = g_new0 (GdaGeometricPoint, 1);

	as_string++;
	point->x = atof (as_string);
	as_string = strchr (as_string, ',');
	as_string++;
	point->y = atof (as_string);

	gda_value_set_geometric_point (dest, point);
	g_free (point);
}
