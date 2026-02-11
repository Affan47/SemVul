parsepathconf(const u_int32_t *dp)
{
	int er;
	struct nfsv3_pathconf *spp;

	if (!(dp = parsestatus(dp, &er)))
		return (0);
	if (vflag)
		printf(" POST:");
	if (!(dp = parse_post_op_attr(dp, vflag)))
		return (0);
	if (er)
		return (1);

	spp = (struct nfsv3_pathconf *)dp;
	TCHECK(*spp);

	printf(" linkmax %u namemax %u %s %s %s %s",
	       EXTRACT_32BITS(&spp->pc_linkmax),
	       EXTRACT_32BITS(&spp->pc_namemax),
	       EXTRACT_32BITS(&spp->pc_notrunc) ? "notrunc" : "",
	       EXTRACT_32BITS(&spp->pc_chownrestricted) ? "chownres" : "",
	       EXTRACT_32BITS(&spp->pc_caseinsensitive) ? "igncase" : "",
	       EXTRACT_32BITS(&spp->pc_casepreserving) ? "keepcase" : "");
	return (1);
trunc:
	return (0);
}
