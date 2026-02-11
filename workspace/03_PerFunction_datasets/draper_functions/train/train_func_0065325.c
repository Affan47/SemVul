identical_file(struct entry *e1, struct entry *e2){
	char *start1, *start2;
	int equal;

	start1 = do_mmap(e1->path, e1->size, e1->mode);
	if (!start1)
		return 0;
	start2 = do_mmap(e2->path, e2->size, e2->mode);
	if (!start2)
		return 0;
	equal = !memcmp(start1, start2, e1->size);
	do_munmap(start1, e1->size, e1->mode);
	do_munmap(start2, e2->size, e2->mode);
	return equal;
}
