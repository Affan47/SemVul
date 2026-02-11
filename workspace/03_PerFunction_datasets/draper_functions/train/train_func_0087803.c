path_normalize(PATHSPLIT *f, PATHSPLIT *cwd)
{
	PATHSPLIT f2;
	int i;

	if (is_relative(f) && (cwd || _cwd))
		f2 = cwd ? *cwd : _fcwd;
	else
		f2.count = 0;

	for (i = 0; i < f->count; i++)
	{
		PATHPART *part = &f->part[i];

		if (part->ptr == _dot)
			continue;

		if (part->ptr == _dotdot)
		{
			if (f2.count == 0)
				return 1;
			--f2.count;
			continue;
		}

		f2.part[f2.count].ptr = part->ptr;
		f2.part[f2.count].len = part->len;
		++f2.count;
	}

	*f = f2;
	return 0;
}
