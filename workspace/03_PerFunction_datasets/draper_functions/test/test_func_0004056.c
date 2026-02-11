compare_filename(struct fileinfo *a, struct fileinfo *b)
{
    if(a->filename == NULL)
	return 1;
    if(b->filename == NULL)
	return -1;
    return strcmp(a->filename, b->filename);
}
