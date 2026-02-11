remove_column_east(level *EditLevel)
{
	if (EditLevel->xlen - 1 < MIN_MAP_LINES)
		return;

	free_glued_obstacles(EditLevel);


	EditLevel->xlen--;


	move_all_objects(EditLevel, 0, 0);
	teleport_to_level_center(EditLevel->levelnum);
}
