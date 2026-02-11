FreeGeneration (heap_t *heap, int g)
{
    gen_t	*gen = heap->gen[g];
    int		i;

    if (gen->fromObj == NIL(mem_obj_t *))
	return;

#ifdef VERBOSE
SayDebug ("FreeGeneration [%d]: [%#x, %#x)\n", g+1, MEMOBJ_BASE(gen->fromObj),
MEMOBJ_BASE(gen->fromObj) + MEMOBJ_SZB(gen->fromObj));
#endif
    if (g < heap->cacheGen) {
	if (gen->cacheObj != NIL(mem_obj_t *)) {
	    if (MEMOBJ_SZB(gen->cacheObj) > MEMOBJ_SZB(gen->fromObj))
		MEM_FreeMemObj (gen->fromObj);
	    else {
		MEM_FreeMemObj (gen->cacheObj);
		gen->cacheObj = gen->fromObj;
	    }
	}
	else
	    gen->cacheObj = gen->fromObj;
    }
    else
	MEM_FreeMemObj (gen->fromObj);


    gen->fromObj = NIL(mem_obj_t *);
    for (i = 0;  i < NUM_ARENAS;  i++) {
	arena_t		*ap = gen->arena[i];
	if (ap->frspBase != NIL(ml_val_t *)) {
	    MarkRegion (BIBOP, ap->frspBase, ap->frspSizeB, AID_UNMAPPED);
	    HeapMon_MarkRegion (heap, ap->frspBase, ap->frspSizeB, AID_UNMAPPED);
	    ap->frspBase = NIL(ml_val_t *);
	    ap->frspSizeB = 0;
	    ap->frspTop = NIL(ml_val_t *);
	}
    }

}
