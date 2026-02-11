G3d_maskOpenOld()
{
    G3D_Region region;


    if (G3d_maskMapExistsVar)
	return 1;

    G3d_maskMapExistsVar = G3d_maskFileExists();

    if (!G3d_maskMapExistsVar)
	return 1;

    if ((G3d_maskMap = G3d_openCellOld(G3D_MASK_MAP, G_mapset(),
				       G3D_DEFAULT_WINDOW, FCELL_TYPE,
				       maskOpenOldCacheDefault))
	== NULL) {
	G3d_error("G3d_maskOpenOld: cannot open mask");

	return 0;
    }

    G3d_getRegionStructMap(G3d_maskMap, &region);
    G3d_setWindowMap(G3d_maskMap, &region);

    return 1;
}
