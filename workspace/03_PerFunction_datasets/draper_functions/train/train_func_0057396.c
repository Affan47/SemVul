free_attachment_list(PATMT **alist)
{
    PATMT  *leading;

    while(alist && *alist){
	leading = (*alist)->next;
	if((*alist)->description)
          fs_give((void **)&(*alist)->description);

	if((*alist)->filename){
	    if((*alist)->flags & A_TMP)
	      if(our_unlink((*alist)->filename) < 0)
		dprint((1, "-- Can't unlink(%s): %s\n",
		       (*alist)->filename ? (*alist)->filename : "?",
		       error_description(errno)));

	    fs_give((void **)&(*alist)->filename);
	}

	if((*alist)->size)
          fs_give((void **)&(*alist)->size);

	if((*alist)->id)
          fs_give((void **)&(*alist)->id);

	fs_give((void **)alist);

	*alist = leading;
    }
}
