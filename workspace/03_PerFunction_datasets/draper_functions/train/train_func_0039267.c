store_open2(const char *path1, const char *path2, int compact, void (*f)(void*,const uuid*,const void*,int), void *p1)
{
	store *st = (store*)calloc(1, sizeof(struct store_));
	if (!st || !path1) return NULL;
	if (!path2) path2 = path1;
	strcpy(st->path1, path1);
	strcpy(st->path2, path2);
	st->f = f;
	st->p1 = p1;
	st->tptr = tree_create();
	st->lk = lock_create();

	if ((mkdir(st->path1, 0777) < 0) && (errno != EEXIST))
	{
		printf("store_open: mkdir '%s' error: %s\n", st->path1, strerror(errno));
		store_close(st);
		return NULL;
	}

	string filename, filename2;
	sprintf(filename, "%s/%s", st->path1, ZEROTH_LOG);
	sprintf(filename2, "%s/%s", st->path1, FIRST_LOG);
	struct stat s = {0};
	stat(filename, &s);
	int do_merge = 0;

	if (compact && (s.st_size > 0))
	{
		printf("store_open: compaction scheduled\n");
		rename(filename, filename2);
		do_merge++;
	}

	if (store_open_file(st, filename, 1, 1))
	{
		printf("store_open_file: '%s'\n", filename);
		store_load_file(st);
	}

	if (store_open_file(st, filename2, 1, 0))
		store_load_file(st);

	if (strcmp(st->path1, st->path2))
	{
		if ((mkdir(st->path2, 0777) < 0) && (errno != EEXIST))
		{
			printf("store_open: mkdir '%s' error: %s\n", st->path2, strerror(errno));
			store_close(st);
			return NULL;
		}
	}


	dirlist(st->path2, ".log", &store_open_handler, st);

	if (st->idx == (MAX_LOGFILES-1))
		do_merge++;

	if (do_merge)
		store_merge(st);


	sprintf(filename, "%s/%lld.log", st->path2, (long long)time(NULL));
	store_open_file(st, filename, 0, 1);
	printf("store_open_file: '%s'\n", filename);
	return st;
}
