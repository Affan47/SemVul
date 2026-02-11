do_proc_douintvec_conv(bool *negp, unsigned long *lvalp,
				 int *valp,
				 int write, void *data)
{
	if (write) {
		if (*negp)
			return -EINVAL;
		if (*lvalp > UINT_MAX)
			return -EINVAL;
		*valp = *lvalp;
	} else {
		unsigned int val = *valp;
		*negp = false;
		*lvalp = (unsigned long)val;
	}
	return 0;
}
