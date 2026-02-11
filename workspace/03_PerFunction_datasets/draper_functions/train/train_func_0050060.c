new_cache_entry(NSSArena *arena, void *value, PRBool ownArena)
{
    cache_entry *ce = nss_ZNEW(arena, cache_entry);
    if (ce) {
	ce->entry.value = value;
	ce->hits = 1;
	ce->lastHit = PR_Now();
	if (ownArena) {
	    ce->arena = arena;
	}
	ce->nickname = NULL;
    }
    return ce;
}
