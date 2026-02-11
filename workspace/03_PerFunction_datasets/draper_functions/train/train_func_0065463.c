sort_thread_flatten(THREADNODE *node, MAILSTREAM *stream,
		    long *entry, char *dup_chk, long maxno,
		    PINETHRD_S *thrd, unsigned int flags)
{
    PINETHRD_S *newthrd = NULL;

    if(node){
	if(node->num > 0L && node->num <= maxno){
	    if(!dup_chk[node->num]){
		*entry = node->num;
		dup_chk[node->num] = 1;


		newthrd = msgno_thread_info(stream, node->num, thrd, flags);
		if(newthrd){
		  entry++;

		  if(node->next)
		    entry = sort_thread_flatten(node->next, stream,
						entry, dup_chk, maxno,
						newthrd, THD_NEXT);

		  if(node->branch)
		    entry = sort_thread_flatten(node->branch, stream,
						entry, dup_chk, maxno,
						newthrd,
						(flags == THD_TOP) ? THD_TOP
								   : THD_BRANCH);
		}
	    }
	}
    }

    return(entry);
}
