ext4_xattr_list_entries(struct dentry *dentry, struct ext4_xattr_entry *entry,
			char *buffer, size_t buffer_size)
{
	size_t rest = buffer_size;

	for (; !IS_LAST_ENTRY(entry); entry = EXT4_XATTR_NEXT(entry)) {
		const struct xattr_handler *handler =
			ext4_xattr_handler(entry->e_name_index);

		if (handler) {
			size_t size = handler->list(handler, dentry, buffer,
						    rest, entry->e_name,
						    entry->e_name_len);
			if (buffer) {
				if (size > rest)
					return -ERANGE;
				buffer += size;
			}
			rest -= size;
		}
	}
	return buffer_size - rest;
}
