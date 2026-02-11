rb_open(int fd, uint8_t type, const char *desc)
{
	rb_fde_t *F;
	lrb_assert(fd >= 0);

	F = add_fd(fd);

	lrb_assert(!IsFDOpen(F));
	if(rb_unlikely(IsFDOpen(F)))
	{
		const char *fdesc;
		if(F != NULL && F->desc != NULL)
			fdesc = F->desc;
		else
			fdesc = "NULL";
		rb_lib_log("Trying to rb_open an already open FD: %d desc: %s", fd, fdesc);
		return NULL;
	}
	F->fd = fd;
	F->type = type;
	SetFDOpen(F);

	if(desc != NULL)
		F->desc = rb_strndup(desc, FD_DESC_SZ);
	number_fd++;
	return F;
}
