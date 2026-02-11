map_baseline (GogAxisMap *map)
{
	const MapData *data = map->data;

	if (0. < data->min)
		return map_linear_to_view (map, data->min);
	else if (0 > data->max)
		return map_linear_to_view (map, data->max);

	return map_linear_to_view (map, 0.);
}
