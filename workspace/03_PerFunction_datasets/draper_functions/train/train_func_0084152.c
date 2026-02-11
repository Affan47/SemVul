xenbus_gather(struct xenbus_transaction t, const char *dir, ...)
{
	va_list ap;
	const char *name;
	int ret = 0;

	va_start(ap, dir);
	while (ret == 0 && (name = va_arg(ap, char *)) != NULL) {
		const char *fmt = va_arg(ap, char *);
		void *result = va_arg(ap, void *);
		char *p;

		p = xenbus_read(t, dir, name, NULL);
		if (IS_ERR(p)) {
			ret = PTR_ERR(p);
			break;
		}
		if (fmt) {
			if (sscanf(p, fmt, result) == 0)
				ret = -EINVAL;
			kfree(p);
		} else
			*(char **)result = p;
	}
	va_end(ap);
	return ret;
}
