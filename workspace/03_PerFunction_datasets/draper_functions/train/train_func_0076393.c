camel_partition_table_remove (CamelPartitionTable *cpi,
                              const gchar *key)
{
	CamelPartitionKeyBlock *pkb;
	CamelPartitionMapBlock *ptb;
	CamelBlock *block, *ptblock;
	camel_hash_t hashid;
	GList *ptblock_link;
	gint index, i;

	g_return_val_if_fail (CAMEL_IS_PARTITION_TABLE (cpi), FALSE);
	g_return_val_if_fail (key != NULL, FALSE);

	hashid = hash_key (key);

	CAMEL_PARTITION_TABLE_LOCK (cpi, lock);

	ptblock_link = find_partition (cpi, hashid, &index);
	if (ptblock_link == NULL) {
		CAMEL_PARTITION_TABLE_UNLOCK (cpi, lock);
		return TRUE;
	}

	ptblock = (CamelBlock *) ptblock_link->data;
	ptb = (CamelPartitionMapBlock *) &ptblock->data;
	block = camel_block_file_get_block (
		cpi->blocks, ptb->partition[index].blockid);
	if (block == NULL) {
		CAMEL_PARTITION_TABLE_UNLOCK (cpi, lock);
		return FALSE;
	}
	pkb = (CamelPartitionKeyBlock *) &block->data;


	for (i = 0; i < pkb->used; i++) {
		if (pkb->keys[i].hashid == hashid) {


			pkb->used--;
			for (; i < pkb->used; i++) {
				pkb->keys[i].keyid = pkb->keys[i + 1].keyid;
				pkb->keys[i].hashid = pkb->keys[i + 1].hashid;
			}
			camel_block_file_touch_block (cpi->blocks, block);
			break;
		}
	}

	CAMEL_PARTITION_TABLE_UNLOCK (cpi, lock);

	camel_block_file_unref_block (cpi->blocks, block);

	return TRUE;
}
