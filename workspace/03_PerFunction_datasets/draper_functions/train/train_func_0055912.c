load_mtree_dictionary(mtree_p mtree, const char* dict_file)
{
    FILE *fp;

    if ((fp = fopen(dict_file, "rt")) == NULL)
	return NULL;
    mtree = mnode_load(mtree, fp);
    fclose(fp);
    return mtree;
}
