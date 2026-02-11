map_log_bounds (GogAxisMap *map, double *minimum, double *maximum)
{
	const MapLogData *data = map->data;

	if (minimum != NULL) *minimum = exp (data->min);
	if (maximum != NULL) *maximum = exp (data->max);
}
