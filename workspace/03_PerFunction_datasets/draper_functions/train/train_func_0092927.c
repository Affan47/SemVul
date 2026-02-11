io_shrink(struct io_context *ioc)
{
	int getfrom, putto = 0;


	for (getfrom = 0; getfrom < ioc->fdcnt; getfrom++) {
		if (ioc->ior[getfrom].id) {

			if (getfrom != putto) {
				ioc->fds[putto] = ioc->fds[getfrom];
				ioc->ior[putto] = ioc->ior[getfrom];
				*(ioc->ior[putto].id) = putto;
			}
			putto++;
		}
	}
	ioc->fdcnt = putto;
	ioc->needshrink = 0;


	return 0;
}
