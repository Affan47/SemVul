fscheck_thread(btree* tree, hfsp_cat_thread* thread)
{
    UInt32  cnid    = tree->vol->vol.next_cnid;
    int	    result  = fscheck_unistr255(&thread->nodeName);

    if (thread->parentID >= cnid)
    {
	printf("Thread parentID %ld >= volume next cnid %ld\n",
		    thread->parentID, cnid);
	result |= FSCK_FSCORR;
    }
    return result;
}
