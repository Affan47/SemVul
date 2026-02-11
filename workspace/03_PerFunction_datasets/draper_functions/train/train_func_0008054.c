vsl_IX_arg(struct VSM_data *vd, const char *opt, int arg)
{
	struct vsl *vsl = vsl_Setup(vd);
	vre_t **rp;
	const char *error;
	int erroroffset;

	CHECK_OBJ_NOTNULL(vd, VSM_MAGIC);
	if (arg == 'I')
		rp = &vsl->regincl;
	else
		rp = &vsl->regexcl;
	if (*rp != NULL)
		return (vsm_diag(vd, "Option %c can only be given once", arg));
	*rp = VRE_compile(opt, vsl->regflags, &error, &erroroffset);
	if (*rp == NULL)
		return (vsm_diag(vd, "Illegal regex: %s\n", error));
	return (1);
}
