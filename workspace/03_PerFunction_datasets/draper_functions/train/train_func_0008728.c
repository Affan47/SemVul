get_a_display(int ix) {
	disppath **paths, *rv = NULL;
	int i;

	if ((paths = get_displays()) == NULL)
		return NULL;

	for (i = 0; ;i++) {
		if (paths[i] == NULL) {
			free_disppaths(paths);
			return NULL;
		}
		if (i == ix)
			break;
	}
	if ((rv = malloc(sizeof(disppath))) == NULL) {
		debugrr("get_a_display failed malloc\n");
		free_disppaths(paths);
		return NULL;
	}
	*rv = *paths[i];
	if ((rv->name = strdup(paths[i]->name)) == NULL) {
		debugrr("get_displays failed on malloc\n");
		free(rv->description);
		free(rv);
		free_disppaths(paths);
		return NULL;
	}
	if ((rv->description = strdup(paths[i]->description)) == NULL) {
		debugrr("get_displays failed on malloc\n");
		free(rv);
		free_disppaths(paths);
		return NULL;
	}
#if defined(UNIX_X11)
	if (paths[i]->edid != NULL) {
		if ((rv->edid = malloc(sizeof(unsigned char) * paths[i]->edid_len)) == NULL) {
			debugrr("get_displays failed on malloc\n");
			free(rv);
			free_disppaths(paths);
			return NULL;
		}
		rv->edid_len = paths[i]->edid_len;
		memmove(rv->edid, paths[i]->edid, rv->edid_len );
	}
#endif
	free_disppaths(paths);
	return rv;
}
