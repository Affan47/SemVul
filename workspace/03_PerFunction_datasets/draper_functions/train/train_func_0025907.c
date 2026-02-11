rcsbuf_cache_close (void)
{
    if (cached_rcs != NULL)
    {
	rcsbuf_close (&cached_rcsbuf);
	if (fclose (cached_rcsbuf.fp) != 0)
	    error (0, errno, "cannot close %s", cached_rcsbuf.filename);
	freercsnode (&cached_rcs);
	cached_rcs = NULL;
    }
}
