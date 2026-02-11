totalChunkArenaSize()
{
    ChunkArenaPtr arena;
    int i, size = 0;

    for(i = 0; i < numArenas; i++) {
        arena = &(chunkArenas[i]);
        if(arena->chunks)
            size += (CHUNK_SIZE * ARENA_CHUNKS);
    }
    return size;
}
