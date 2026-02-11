get_lkcd_panic_task(void)
{
	return(lkcd->flags & (LKCD_VALID|LKCD_REMOTE) ? lkcd->panic_task : 0);
}
