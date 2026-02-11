load_map(int issave, unsigned char *udata, unsigned usize)
{
	unsigned char *iptr;
	unsigned isize;
	unsigned char *xptr;
	unsigned xsize = getdwordle(udata + 4);
	unsigned xofs = getdwordle(udata + 0);
	if (issave)
	{
		iptr = loaderwork.state;
		isize = loaderwork.statesize;
		loaderwork.state = 0;
		loaderwork.statesize = 0;
	}
	else
	{
		iptr = loaderwork.rom;
		isize = loaderwork.romsize;
		loaderwork.rom = 0;
		loaderwork.romsize = 0;
	}
	if (!iptr)
	{
		iptr = malloc(xofs + xsize + 10);
		if (!iptr)
			return XSF_FALSE;
		memset(iptr, 0, xofs + xsize + 10);
		isize = xofs + xsize;
	}
	else if (isize < xofs + xsize)
	{
		unsigned rsize = xofs + xsize;
		if (!issave)
		{
			rsize -= 1;
			rsize |= rsize >> 1;
			rsize |= rsize >> 2;
			rsize |= rsize >> 4;
			rsize |= rsize >> 8;
			rsize |= rsize >> 16;
			rsize += 1;
		}
		xptr = realloc(iptr, xofs + rsize + 10);
		if (!xptr)
		{
			free(iptr);
			return XSF_FALSE;
		}
		iptr = xptr;
		isize = rsize;
	}
	memcpy(iptr + xofs, udata + 8, xsize);
	if (issave)
	{
		loaderwork.state = iptr;
		loaderwork.statesize = isize;
	}
	else
	{
		loaderwork.rom = iptr;
		loaderwork.romsize = isize;
	}
	return XSF_TRUE;
}
