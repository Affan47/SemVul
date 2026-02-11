policydb_class_isvalid(struct policydb *p, unsigned int class)
{
	if (!class || class > p->p_classes.nprim)
		return 0;
	return 1;
}
