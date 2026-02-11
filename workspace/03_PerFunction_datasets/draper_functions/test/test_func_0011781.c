storeUfsUnlink(SwapDir * SD, StoreEntry * e)
{
    debug(79, 3) ("storeUfsUnlink: fileno %08X\n", e->swap_filen);
    storeUfsDirReplRemove(e);
    storeUfsDirMapBitReset(SD, e->swap_filen);
    storeUfsDirUnlinkFile(SD, e->swap_filen);
}
