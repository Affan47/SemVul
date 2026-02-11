map_bounds (GogAxisMap *map, double *minimum, double *maximum)
{
	const MapData *data = map->data;

	if (minimum != NULL) *minimum = data->min;
	if (maximum != NULL) *maximum = data->max;
}
