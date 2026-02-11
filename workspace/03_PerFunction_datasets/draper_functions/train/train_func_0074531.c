discardCache(CacheTypes caches)
{
    if (caches & PixmapCache) {
        pixmapsToCache.clear();
        saveTimer->stop();
        if (pixmapCache) {
            pixmapCache->clear();
        }
    } else {

        delete pixmapCache;
        pixmapCache = 0;
    }

    cachedStyleSheets.clear();

    if (caches & SvgElementsCache) {
        discoveries.clear();
        invalidElements.clear();
        svgElementsCache = 0;
    }
}
