expand_cell_name(const char *cell)
{
    FILE *f;
    const char *c;
    const char **fn, *fns[] = { _PATH_CELLSERVDB,
				_PATH_ARLA_CELLSERVDB,
				_PATH_OPENAFS_DEBIAN_CELLSERVDB,
				_PATH_ARLA_DEBIAN_CELLSERVDB,
				NULL };
    for(fn = fns; *fn; fn++) {
	f = fopen(*fn, "r");
	if(f == NULL)
	    continue;
	c = expand_one_file(f, cell);
	fclose(f);
	if(c)
	    return c;
    }
    return cell;
}
