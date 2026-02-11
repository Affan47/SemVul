arenaFree( Arena *arena )
{
    bdescr *bd, *next;

    for (bd = arena->current; bd != NULL; bd = next) {
	next = bd->link;
	arena_blocks -= bd->blocks;
	ASSERT(arena_blocks >= 0);
	freeGroup_lock(bd);
    }
    stgFree(arena);
}
