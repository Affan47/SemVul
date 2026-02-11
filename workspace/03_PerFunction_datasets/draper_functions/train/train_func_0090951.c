name_hash(struct fuse *f, fuse_ino_t parent,
			const char *name)
{
	uint64_t hash = parent;
	uint64_t oldhash;

	for (; *name; name++)
		hash = hash * 31 + (unsigned char) *name;

	hash %= f->name_table.size;
	oldhash = hash % (f->name_table.size / 2);
	if (oldhash >= f->name_table.split)
		return oldhash;
	else
		return hash;
}
