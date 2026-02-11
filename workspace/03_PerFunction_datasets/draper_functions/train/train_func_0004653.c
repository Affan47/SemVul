giblorb_unload_chunk(giblorb_map_t *map, glui32 chunknum)
{
    giblorb_chunkdesc_t *chu;

    if (chunknum < 0 || chunknum >= map->numchunks)
        return giblorb_err_NotFound;

    chu = &(map->chunks[chunknum]);

    if (chu->ptr) {
        giblorb_free(chu->ptr);
        chu->ptr = NULL;
    }

    return giblorb_err_None;
}
