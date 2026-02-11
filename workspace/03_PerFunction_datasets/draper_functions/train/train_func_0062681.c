pl_TopAccept (
    PRFileDesc *fd, PRNetAddr *addr, PRIntervalTime timeout)
{
    PRStatus rv;
    PRFileDesc *newfd, *layer = fd;
    PRFileDesc *newstack;
	PRBool newstyle_stack = PR_FALSE;

    PR_ASSERT(fd != NULL);
    PR_ASSERT(fd->lower != NULL);


	while (NULL != layer->higher)
		layer = layer->higher;
	newstyle_stack = (PR_IO_LAYER_HEAD == layer->identity) ? PR_TRUE : PR_FALSE;
    newstack = PR_NEW(PRFileDesc);
    if (NULL == newstack)
    {
        PR_SetError(PR_OUT_OF_MEMORY_ERROR, 0);
        return NULL;
    }
    *newstack = *fd;

    newfd = (fd->lower->methods->accept)(fd->lower, addr, timeout);
    if (NULL == newfd)
    {
        PR_DELETE(newstack);
        return NULL;
    }

    if (newstyle_stack) {
		newstack->lower = newfd;
		newfd->higher = newstack;
		return newstack;
	} else {

		rv = PR_PushIOLayer(newfd, PR_TOP_IO_LAYER, newstack);
		PR_ASSERT(PR_SUCCESS == rv);
    	return newfd;
	}
}
