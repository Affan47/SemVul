nssList_Create
(
  NSSArena *arenaOpt,
  PRBool threadSafe
)
{
    NSSArena *arena;
    nssList *list;
    PRBool i_alloced;
    if (arenaOpt) {
	arena = arenaOpt;
	i_alloced = PR_FALSE;
    } else {
	arena = nssArena_Create();
	i_alloced = PR_TRUE;
    }
    if (!arena) {
	return (nssList *)NULL;
    }
    list = nss_ZNEW(arena, nssList);
    if (!list) {
	if (!arenaOpt) {
	    NSSArena_Destroy(arena);
	}
	return (nssList *)NULL;
    }
    if (threadSafe) {
	list->lock = PZ_NewLock(nssILockOther);
	if (!list->lock) {
	    if (arenaOpt) {
		nss_ZFreeIf(list);
	    } else {
		NSSArena_Destroy(arena);
	    }
	    return (nssList *)NULL;
	}
    }
    list->arena = arena;
    list->i_alloced_arena = i_alloced;
    list->compareFunc = pointer_compare;
    return list;
}
