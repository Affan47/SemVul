save(char_u *buf, int len)
{
    queue_T *node;

    node = (queue_T *)alloc(sizeof(queue_T));
    if (node == NULL)
	return;
    node->buffer = alloc(len + 1);
    if (node->buffer == NULL)
    {
	vim_free(node);
	return;
    }
    mch_memmove(node->buffer, buf, (size_t)len);
    node->buffer[len] = NUL;

    if (head.next == NULL)
    {
	head.next = &head;
	head.prev = &head;
    }


    node->next = &head;
    node->prev = head.prev;
    head.prev->next = node;
    head.prev = node;

#ifdef NBDEBUG
    {
	static int outfd = -2;


	if (outfd == -3)
	    return;

	if (outfd == -2)
	{
	    char *file = getenv("__NETBEANS_SAVE");
	    if (file == NULL)
		outfd = -3;
	    else
		outfd = mch_open(file, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	}

	if (outfd >= 0)
	    write(outfd, buf, len);
    }
#endif
}
