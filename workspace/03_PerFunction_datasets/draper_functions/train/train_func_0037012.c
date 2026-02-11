named_fifo_buffered_precheckpoint(void *p)
{
    int retval;
    struct test_fifo_struct *f = p;

    switch((f->flags) & O_ACCMODE) {
      case O_RDONLY:

	retval = write_atomic(f->rdwr_fd);
	break;
      case O_WRONLY:
      case O_RDWR:

	retval = write_atomic(f->client_fd);
	break;
      default:
	retval = -1;
    }
    if (retval < 0) goto out;

    retval = fstat(f->rdwr_fd, &f->stat);
    if (retval < 0) {
	perror("fstat");
    }

out:
    return retval;
}
