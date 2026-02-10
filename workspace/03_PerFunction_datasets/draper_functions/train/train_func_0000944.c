G3d_writeTileDouble(G3D_Map * map, int tileIndex, const void *tile)
{
    int status;

    if ((status = G3d_writeTile(map, tileIndex, tile, DCELL_TYPE)))
	return status;

    G3d_error("G3d_writeTileDouble: error in G3d_writeTile");
    return 0;
}
