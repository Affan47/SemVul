closeFifo(struct FifoData *p)
{
    struct stat st;

    if (p->input >= 0) {
	close(p->input);
	p->input = -1;
    }

    if ((p->created >= 0) && (stat(p->path, &st) == 0)) {
	debug("Removing FIFO \"%s\"\n", p->path);
	if (unlink(p->path) < 0) {
	    error("Could not remove FIFO \"%s\": %s\n", p->path, strerror(errno));

	    return;
	}
	p->created = -1;
    }

    if (p->msg) {
	free(p->msg);
	p->msg = p->path = NULL;
	p->msglen = -1;
    }
}
