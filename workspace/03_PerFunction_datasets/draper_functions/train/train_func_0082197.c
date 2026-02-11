do_forget(struct fuse *f, fuse_ino_t ino, uint64_t nlookup)
{
	if (f->conf.debug)
		fprintf(stderr, "FORGET %llu/%llu\n", (unsigned long long)ino,
			(unsigned long long) nlookup);
	forget_node(f, ino, nlookup);
}
