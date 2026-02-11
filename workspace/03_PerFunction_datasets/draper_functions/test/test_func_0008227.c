fdset_del_fd(struct fdset *fds, int fd)
{
    struct fdset_node *fn;

    for (fn = PTR fds->list->first; fn->node->next; fn = PTR fn->node->next)
	if (fn->fd == fd)
	{
	    dl_remove(fn->node);
	    free(fn);
	    fds->del_count++;
	    return 0;
	}
    return -1;
}
