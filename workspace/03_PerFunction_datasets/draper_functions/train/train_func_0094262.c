free_map_labels(level *lvl)
{
	struct map_label *map_label;
	int i;

	for (i = 0; i < lvl->map_labels.size; i++) {

		map_label = &ACCESS_MAP_LABEL(lvl->map_labels, i);

		free(map_label->label_name);
	}

	dynarray_free(&lvl->map_labels);
}
