change_extensions(level *lvl, obstacle *from, obstacle *to)
{
	int i;
	struct obstacle_extension *ext;

	for (i = 0; i < lvl->obstacle_extensions.size; i++) {
		ext = &ACCESS_OBSTACLE_EXTENSION(lvl->obstacle_extensions, i);
		if (ext->obs == from) {
			ext->obs = to;
		}
	}
}
