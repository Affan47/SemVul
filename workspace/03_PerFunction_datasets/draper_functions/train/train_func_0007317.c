doconvtoutf8_write(const char *p, size_t n,
			       void *void_arg)
{
	struct doconvtoutf8_info *ptr=
		(struct doconvtoutf8_info *)void_arg;

	if (n && ptr->err_flag == 0)
		ptr->err_flag=(*ptr->callback->output_func)
			(p, n, ptr->callback->arg);
}
