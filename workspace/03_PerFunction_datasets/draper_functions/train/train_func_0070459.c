helperFree(helper * hlp)
{
    if (!hlp)
	return;

    if (hlp->queue.head)
	debug(84, 0) ("WARNING: freeing %s helper with %d requests queued\n",
	    hlp->id_name, hlp->stats.queue_size);
    cbdataFree(hlp);
}
