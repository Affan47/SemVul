map_type(const char *name, int mod)
{
    char *mapset, *tmpname;
    int result;

    switch (mod) {
    case 'M':
	tmpname = G_store((char *)name);
	mapset = G_find_grid3(tmpname, "");
	if (mapset) {
	    void *handle;

	    setup_region();
	    handle = G3d_openCellOld(tmpname, mapset, &current_region3,
				     G3D_TILE_SAME_AS_FILE, G3D_NO_CACHE);
	    result = (G3d_fileTypeMap(handle) == FCELL_TYPE)
		? FCELL_TYPE : DCELL_TYPE;
	    G3d_closeCell(handle);
	}
	else
	    result = -1;
	G_free(tmpname);
	return result;
    case '@':
	return DCELL_TYPE;
    case 'r':
    case 'g':
    case 'b':
    case '#':
    case 'y':
    case 'i':
	return CELL_TYPE;
    default:
	G_fatal_error(_("Invalid map modifier: '%c'"), mod);
	return -1;
    }
}
