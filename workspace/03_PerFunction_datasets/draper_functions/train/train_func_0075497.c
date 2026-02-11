get_existing_callback(const char *f, void *vp)
{
	char **fn;

	struct get_existing_folder_info *gefi=
		(struct get_existing_folder_info *)vp;
	size_t i;
	size_t j;

	if (gefi->pathname)
		return;

	fn=maildir_smapfn_fromutf7(f);
	if (!fn)
	{
		perror(f);
		return;
	}

	for (i=0; gefi->fn[i]; i++)
		if (fn[i] == NULL || strcmp(fn[i], gefi->fn[i]))
		{
			maildir_smapfn_free(fn);
			return;
		}

	maildir_smapfn_free(fn);

	for (j=0; i && f[j]; j++)
		if (f[j] == '.' && f[j+1] && f[j+1] != '.')
		{
			--i;
			if (i == 0)
				break;
		}

	gefi->pathname=malloc(j+1);

	if (!gefi->pathname)
	{
		perror("malloc");
		return;
	}

	memcpy(gefi->pathname, f, j);
	gefi->pathname[j]=0;
}
