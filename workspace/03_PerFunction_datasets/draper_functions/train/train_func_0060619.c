copyout_macb(record *src, const char *dstname)
{
    int ofile, result = 0;

    if (openfiles(src, dstname, ".bin", &ofile))
	return -1;

    result = do_macb(src, ofile);

    result = closefiles(src, ofile) || result;

    return result;
}
