xensyms_next(struct seq_file *m, void *p, loff_t *pos)
{
	struct xensyms *xs = (struct xensyms *)m->private;

	xs->op.u.symdata.symnum = ++(*pos);

	if (xensyms_next_sym(xs))
		return NULL;

	return p;
}
