GetCacheMB(int size)
{
    if (size <= 0)
        return 0;
    else
        return (1 << (size + 15)) * sizeof(cacheNode) / (1024 * 1024);
}
