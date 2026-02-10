cache_chid(aChannel *chptr)
{


    if (chptr->history == 0 ||
	(timeofday - chptr->history) >LDELAYCHASETIMELIMIT+DELAYCHASETIMELIMIT)
	{
	    MyFree(chptr);
	    return;
	}

    chptr->nextch = idcache;
    idcache = chptr;
    istat.is_cchan++;
    istat.is_cchanmem += sizeof(aChannel) + strlen(chptr->chname);
}
