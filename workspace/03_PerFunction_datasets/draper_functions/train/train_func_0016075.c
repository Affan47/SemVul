commit_bonesfile(lev)
d_level *lev;
{
	const char *fq_bones, *tempname;
	int ret;

	(void) set_bonesfile_name(bones, lev);
	fq_bones = fqname(bones, BONESPREFIX, 0);
	tempname = set_bonestemp_name();
	tempname = fqname(tempname, BONESPREFIX, 1);

#if (defined(SYSV) && !defined(SVR4)) || defined(GENIX)


	(void) unlink(fq_bones);
	ret = link(tempname, fq_bones);
	ret += unlink(tempname);
#else
	ret = rename(tempname, fq_bones);
#endif
#ifdef WIZARD
	if (wizard && ret != 0)
		pline("couldn't rename %s to %s.", tempname, fq_bones);
#endif
}
