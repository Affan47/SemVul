gog_axis_map (GogAxisMap *map, double value)
{
	g_return_val_if_fail (map != NULL, -1);

	return (map->axis->inverted
		? 1.0 - map->desc->map (map, value)
		: map->desc->map (map, value));
}
