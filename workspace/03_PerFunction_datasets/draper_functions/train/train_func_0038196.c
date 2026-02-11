pl_DefAcceptread (
    PRFileDesc *sd, PRFileDesc **nd, PRNetAddr **raddr, void *buf,
    PRInt32 amount, PRIntervalTime t)
{
    PRInt32 nbytes;
    PRStatus rv;
    PRFileDesc *newstack;
    PRFileDesc *layer = sd;
	PRBool newstyle_stack = PR_FALSE;

    PR_ASSERT(sd != NULL);
    PR_ASSERT(sd->lower != NULL);


	while (NULL != layer->higher)
		layer = layer->higher;
	newstyle_stack = (PR_IO_LAYER_HEAD == layer->identity) ? PR_TRUE : PR_FALSE;
    newstack = PR_NEW(PRFileDesc);
    if (NULL == newstack)
    {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        return -1;
    }
    *newstack = *sd;

    nbytes = sd->lower->methods->acceptread(
        sd->lower, nd, raddr, buf, amount, t);
    if (-1 == nbytes)
    {
        PR_DELETE(newstack);
        return nbytes;
    }
    if (newstyle_stack) {
		newstack->lower = *nd;
		(*nd)->higher = newstack;
		*nd = newstack;
		return nbytes;
	} else {

		rv = PR_PushIOLayer(*nd, PR_TOP_IO_LAYER, newstack);
		PR_ASSERT(PR_SUCCESS == rv);
		return nbytes;
	}
}
