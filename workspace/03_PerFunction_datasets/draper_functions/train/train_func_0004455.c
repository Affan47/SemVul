G3d_cacheSizeEncode(int cacheCode, int n)
{
    if (cacheCode >= G3D_NO_CACHE)
	return cacheCode * n;
    if (cacheCode == G3D_USE_CACHE_DEFAULT)
	return cacheCode;

    if (cacheCode < G3D_USE_CACHE_XYZ)
	G3d_fatalError("G3d_cacheSizeEncode: invalid cache code");

    return n * (-10) + cacheCode;
}
