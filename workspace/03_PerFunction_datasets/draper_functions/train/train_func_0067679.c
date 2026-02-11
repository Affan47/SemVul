storeClientType(StoreEntry * e)
{
    MemObject *mem = e->mem_obj;
    if (mem->inmem_lo)
	return STORE_DISK_CLIENT;
    if (EBIT_TEST(e->flags, ENTRY_ABORTED)) {

	debug(20, 1) ("storeClientType: adding to ENTRY_ABORTED entry\n");
	return STORE_MEM_CLIENT;
    }
    if (e->store_status == STORE_OK) {
	if (mem->inmem_lo == 0 && mem->inmem_hi > 0)
	    return STORE_MEM_CLIENT;
	else
	    return STORE_DISK_CLIENT;
    }


    else if (mem->nclients == 1)
	return STORE_MEM_CLIENT;


    else if (e->swap_status == SWAPOUT_NONE)
	return STORE_MEM_CLIENT;


    else
	return STORE_DISK_CLIENT;
}
