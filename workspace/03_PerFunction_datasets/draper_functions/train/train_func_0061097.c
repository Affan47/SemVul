validate_obstacle_graphics(void)
{
	int i, j;
	for (i = 0; i < obstacle_map.size; i++) {
		struct obstacle_graphics *graphics = &((struct obstacle_graphics *)obstacle_images.arr)[i];
		for (j = 0; j < graphics->count; j++) {
			const char *filename = ((char **)get_obstacle_spec(i)->filenames.arr)[j];
			if (!image_loaded(&graphics->images[j])) {
				if (strcmp(filename, "DUMMY OBSTACLE")) {
					ErrorMessage(__FUNCTION__, "Could not load the image '%s' for obstacle %d.",
						PLEASE_INFORM, IS_WARNING_ONLY, filename, i);
				}
			}
		}
	}
}
