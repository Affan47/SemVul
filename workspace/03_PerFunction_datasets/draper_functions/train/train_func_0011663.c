invalidateMmapFiles()
{
    if (!q->isValid())
        return;

    if (mIndexMmapInfo.file) {
        kDebug(264) << "Invalidating cache";
        mIndexMmapInfo.indexHeader->cacheId = 0;
    }
}
