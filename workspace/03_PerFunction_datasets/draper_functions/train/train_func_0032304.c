ext2fs_add_dir_block2(ext2_dblist dblist, ext2_ino_t ino,
				blk64_t blk, e2_blkcnt_t blockcnt)
{
	struct ext2_db_entry2 	*new_entry;
	errcode_t		retval;
	unsigned long		old_size;

	EXT2_CHECK_MAGIC(dblist, EXT2_ET_MAGIC_DBLIST);

	if (dblist->count >= dblist->size) {
		old_size = dblist->size * sizeof(struct ext2_db_entry2);
		dblist->size += dblist->size > 200 ? dblist->size / 2 : 100;
		retval = ext2fs_resize_mem(old_size, (size_t) dblist->size *
					   sizeof(struct ext2_db_entry2),
					   &dblist->list);
		if (retval) {
			dblist->size = old_size / sizeof(struct ext2_db_entry2);
			return retval;
		}
	}
	new_entry = dblist->list + ( dblist->count++);
	new_entry->blk = blk;
	new_entry->ino = ino;
	new_entry->blockcnt = blockcnt;

	dblist->sorted = 0;

	return 0;
}
