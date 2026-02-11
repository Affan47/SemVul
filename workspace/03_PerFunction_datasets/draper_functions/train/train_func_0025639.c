gfs_dirplusxattr_clear(GFS_DirPlusXAttr dir)
{
	int i, j, n = dir->n, nattrs;
	char **attrs;
	void **values;
	size_t *sizes;

	for (i = 0; i < n; i++) {
		gfs_stat_free(&dir->stbuf[i]);
		nattrs = dir->nattrbuf[i];
		attrs = dir->attrnamebuf[i];
		values = dir->attrvaluebuf[i];
		sizes = dir->attrsizebuf[i];
		for (j = 0; j < nattrs; j++) {
			free(attrs[j]);
			free(values[j]);
		}
		free(attrs);
		free(values);
		free(sizes);
	}
	dir->n = dir->index = 0;
}
