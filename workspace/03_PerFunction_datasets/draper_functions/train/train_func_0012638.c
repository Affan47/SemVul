G3d_getFloatRegion(G3D_Map * map, int x, int y, int z)
{
    int tileIndex, offs;
    float *tile;

    if (map->typeIntern == DCELL_TYPE)
	return (float)G3d_getDoubleRegion(map, x, y, z);

    G3d_coord2tileIndex(map, x, y, z, &tileIndex, &offs);
    tile = (float *)G3d_getTilePtr(map, tileIndex);

    if (tile == NULL)
	G3d_fatalError("G3d_getFloatRegion: error in G3d_getTilePtr");

    return tile[offs];
}
