deallocate(void *ptr)
{
    int i;

    for (i = 0; i < next_pool_slot; i++) {
	if (ptr == pool[i].ptr) {
	    myfree(ptr, pool[i].type);
	    pool[i].ptr = 0;
	    return;
	}
    }

    errlog("DEALLOCATE: Unknown pointer deallocated\n");
}
