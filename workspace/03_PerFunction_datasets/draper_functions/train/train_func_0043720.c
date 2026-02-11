internal_dump_inode_extra(FILE *out,
				      const char *prefix EXT2FS_ATTR((unused)),
				      ext2_ino_t inode_num EXT2FS_ATTR((unused)),
				      struct ext2_inode_large *inode)
{
	struct ext2_ext_attr_entry *entry;
	__u32 *magic;
	char *start, *end;
	unsigned int storage_size;

	fprintf(out, "Size of extra inode fields: %u\n", inode->i_extra_isize);
	if (inode->i_extra_isize > EXT2_INODE_SIZE(current_fs->super) -
			EXT2_GOOD_OLD_INODE_SIZE) {
		fprintf(stderr, "invalid inode->i_extra_isize (%u)\n",
				inode->i_extra_isize);
		return;
	}
	storage_size = EXT2_INODE_SIZE(current_fs->super) -
			EXT2_GOOD_OLD_INODE_SIZE -
			inode->i_extra_isize;
	magic = (__u32 *)((char *)inode + EXT2_GOOD_OLD_INODE_SIZE +
			inode->i_extra_isize);
	if (*magic == EXT2_EXT_ATTR_MAGIC) {
		fprintf(out, "Extended attributes stored in inode body: \n");
		end = (char *) inode + EXT2_INODE_SIZE(current_fs->super);
		start = (char *) magic + sizeof(__u32);
		entry = (struct ext2_ext_attr_entry *) start;
		while (!EXT2_EXT_IS_LAST_ENTRY(entry)) {
			struct ext2_ext_attr_entry *next =
				EXT2_EXT_ATTR_NEXT(entry);
			if (entry->e_value_size > storage_size ||
					(char *) next >= end) {
				fprintf(out, "invalid EA entry in inode\n");
				return;
			}
			fprintf(out, "  ");
			dump_xattr_string(out, EXT2_EXT_ATTR_NAME(entry),
					  entry->e_name_len);
			fprintf(out, " = \"");
			dump_xattr_string(out, start + entry->e_value_offs,
						entry->e_value_size);
			fprintf(out, "\" (%u)\n", entry->e_value_size);
			entry = next;
		}
	}
}
