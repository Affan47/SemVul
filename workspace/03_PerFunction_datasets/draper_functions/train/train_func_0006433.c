G3d_tileInRange(G3D_Map * map, int x, int y, int z)
{
    return (x >= 0) && (x < map->nx) && (y >= 0) && (y < map->ny) &&
	(z >= 0) && (z < map->nz);
}
