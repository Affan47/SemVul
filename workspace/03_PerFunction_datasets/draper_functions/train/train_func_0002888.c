ext2fs_ext_attr_hash_entry(struct ext2_ext_attr_entry *entry, void *data)
{
	__u32 hash = 0;
	char *name = ((char *) entry) + sizeof(struct ext2_ext_attr_entry);
	int n;

	for (n = 0; n < entry->e_name_len; n++) {
		hash = (hash << NAME_HASH_SHIFT) ^
		       (hash >> (8*sizeof(hash) - NAME_HASH_SHIFT)) ^
		       *name++;
	}


	if (entry->e_value_block == 0 && entry->e_value_size != 0) {
		__u32 *value = (__u32 *)data;
		for (n = (entry->e_value_size + EXT2_EXT_ATTR_ROUND) >>
			 EXT2_EXT_ATTR_PAD_BITS; n; n--) {
			hash = (hash << VALUE_HASH_SHIFT) ^
			       (hash >> (8*sizeof(hash) - VALUE_HASH_SHIFT)) ^
			       ext2fs_le32_to_cpu(*value++);
		}
	}

	return hash;
}
