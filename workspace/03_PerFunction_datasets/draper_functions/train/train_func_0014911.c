flushcache(devp)
CONST devstat *devp;
{
	int i, n;

	n = 0;
	for (i = maxsectcache - 1; i >= 0; i--) {
		if (cachedrive[i] != devp -> drive) continue;
		if (cachewrite[i] && !(devp -> flags & F_RONLY)
		&& realwrite(devp, sectno[i], sectcache[i], 1) < 0)
			n = -1;
		cachewrite[i] = 0;
	}

	return(n);
}
