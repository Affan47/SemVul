move_obj_to_storage(struct mem_obj *obj, struct storage_st **st,
		    struct disk_ref **chain)
{
struct	storage_st	*storage, *ostorage;
uint32_t		needed_blocks, obj_size = 0;
struct	buff		*b;
uint32_t		*blk;
struct	disk_ref	*disk_ref;

    if ( *chain ) *chain = NULL;
    if ( !obj )
	return 0;
    b = obj->container;
    if ( !b )
	return 0;

    obj_size = obj->size;

    if ( !obj_size )
	return 0;

    needed_blocks = ROUND(obj_size, BLKSIZE)/BLKSIZE;
    my_xlog(OOPS_LOG_STOR|OOPS_LOG_DBG, "move_obj_to_storage(): Allocate %u disk blocks for object.\n",
	    needed_blocks);

    storage = ostorage = next_alloc_storage;
    if ( !ostorage ) storage = storages;
    while( storage ) {
	WRLOCK_STORAGE(storage);
	if ( (storage->flags & ST_READY) && !(storage->flags & ST_FORCE_CLEANUP) ) {
	    if ( (disk_ref = (struct disk_ref*)request_free_blks(storage, needed_blocks)) !=0 ) {
		blk = (uint32_t*)((char*)disk_ref + sizeof(struct disk_ref));
		MY_TNF_PROBE_0(buff_to_blks_start, "contention", "buff_to_blks begin");
		buff_to_blks(obj->container, storage, blk, needed_blocks);
		MY_TNF_PROBE_0(buff_to_blks_stop, "contention", "buff_to_blks stop");
		*st = storage;
		UNLOCK_STORAGE(storage);
		next_alloc_storage = storage->next;
		*chain = disk_ref;
		return needed_blocks;
	    }
	}
	UNLOCK_STORAGE(storage);
	storage = storage->next;
	if ( storage == ostorage ) break;
	if ( !storage ) storage = storages;
    }
    return 0;
}
