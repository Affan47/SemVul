collect_chid(void)
{
    aChannel **chptr = &idcache, *del;

    while (*chptr)
	{
	    if (close_chid((*chptr)->chname) == 0)
		{
		    del = *chptr;
		    *chptr = del->nextch;
		    istat.is_cchan--;
		    istat.is_cchanmem -= sizeof(aChannel) +strlen(del->chname);
		    MyFree(del);
		}
	    else
		    chptr = &((*chptr)->nextch);
	}
}
