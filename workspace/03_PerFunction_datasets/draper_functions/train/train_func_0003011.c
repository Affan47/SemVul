G3d_minUnlocked(G3D_Map * map, int minUnlocked)
{
    if (!map->useCache)
	G3d_fatalError("G3d_autoLockOff: function invalid in non-cache mode");

    G3d_cache_set_minUnlock(map->cache,
			    G3d__computeCacheSize(map, minUnlocked));
}
