G3d_writeTileUncompressed(G3D_Map * map, int nofNum)
{
    if (write(map->data_fd, xdr, map->numLengthExtern * nofNum) !=
	map->numLengthExtern * nofNum) {
	G3d_error("G3d_writeTileUncompressed: can't write file.");
	return 0;
    }

    return 1;
}
