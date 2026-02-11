disposeCacheWrite(G3D_Map * map)
{
    if (map->cacheFD >= 0) {
	if (close(map->cacheFD) != 0) {
	    G3d_error("disposeCacheWrite: could not close file");
	    return 0;
	}
	remove(map->cacheFileName);
	G3d_free(map->cacheFileName);
    }

    G3d_cache_dispose(map->cache);

    return 1;
}
