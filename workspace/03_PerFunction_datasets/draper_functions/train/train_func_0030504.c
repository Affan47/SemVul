invalidateCache()
{
	DPRINTF("invalidateCache()\n");
	current_time++;
	if ((current_time % 50)==0) {

		reset();
	}
}
