same_suspect(struct origin *a, struct origin *b)
{
	if (a == b)
		return 1;
	if (a->commit != b->commit)
		return 0;
	return !strcmp(a->path, b->path);
}
