action_set_floor_layer(Level EditLevel, int x, int y, int layer, int type)
{
	if (layer >= EditLevel->floor_layers)
		EditLevel->floor_layers++;

	int old = EditLevel->map[y][x].floor_values[layer];
	EditLevel->map[y][x].floor_values[layer] = type;
	action_push(ACT_TILE_FLOOR_SET, x, y, layer, old);
}
