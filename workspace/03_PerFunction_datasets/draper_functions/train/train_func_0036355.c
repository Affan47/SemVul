store_apply(store *st, int n, uint64_t pos)
{
	int fd = st->fd[st->idx-1];
	int cnt = 0;

	if (st->transactions)
		lock_lock(st->lk);

	for (;;)
	{
		char tmpbuf[1024];

		if (pread(fd, tmpbuf, sizeof(tmpbuf), pos) <= 0)
			return 0;

		unsigned nbr, flags, nbytes;
		uuid u;

		int skip = parse(tmpbuf, &nbr, &u, &flags, &nbytes);

		if (flags == TR_BEGIN)
		{
		}
		else if (flags == TR_CANCEL)
		{
			if (nbr == n)
				break;
		}
		else if (flags == TR_END)
		{
			if (nbr == n)
				break;
		}
		else
		{
			if (nbr == n)
			{
				if (!(flags & FLAG_RM))
				{
					int idx = st->idx-1;
					uint64_t fp = MAKE_FILEPOS(idx,pos);
					tree_add(st->tptr, &u, fp);
				}
				else
					tree_del(st->tptr, &u);

				if (st->f)
				{
					if (nbytes)
					{
						char *src = tmpbuf+skip;
						int big = 0;

						if ((src+nbytes) >= (tmpbuf+sizeof(tmpbuf)))
						{
							big = 1;
							src = (char*)malloc(nbytes+1);

							if (pread(fd, src, nbytes, pos+skip) <= 0)
								break;

							src[nbytes] = 0;
						}

						st->f(st->p1, &u, src, flags&FLAG_RM?-nbytes:nbytes);
						if (big) free(src);
					}
					else
						st->f(st->p1, &u, NULL, 0);
				}

				cnt++;
			}
		}

		pos += skip;
		pos += nbytes;
	}

	if (st->transactions)
		lock_unlock(st->lk);

	return cnt;
}
