getFirstMBlock(void)
{
    MBlockMap *map = mblock_maps[0];
    nat line_no, off;
    MbcCacheLine line;

    for (line_no = 0; line_no < MBLOCK_MAP_ENTRIES; line_no++) {
        line = map->lines[line_no];
        if (line) {
            for (off = 0; off < MBC_LINE_SIZE; off++) {
                if (line & (1<<off)) {
                    return (void*)(((StgWord)map->addrHigh32 << 32) +
                                   line_no * MBC_LINE_SIZE * MBLOCK_SIZE +
                                   off * MBLOCK_SIZE);
                }
            }
        }
    }
    return NULL;
}
