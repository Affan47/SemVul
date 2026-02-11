G3d_tileIndexInRange(G3D_Map * map, int tileIndex)
{
    return (tileIndex < map->nTiles) && (tileIndex >= 0);
}
