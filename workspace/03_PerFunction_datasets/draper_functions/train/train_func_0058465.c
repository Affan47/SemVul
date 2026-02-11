nfsreq_print(register const u_char *bp, u_int length,
    register const u_char *bp2)
{
	register const struct sunrpc_msg *rp;
	char srcid[20], dstid[20];

	nfserr = 0;
	rp = (const struct sunrpc_msg *)bp;

	TCHECK(rp->rm_xid);
	if (!nflag) {
		snprintf(srcid, sizeof(srcid), "%u",
		    EXTRACT_32BITS(&rp->rm_xid));
		strlcpy(dstid, "nfs", sizeof(dstid));
	} else {
		snprintf(srcid, sizeof(srcid), "%u",
		    EXTRACT_32BITS(&rp->rm_xid));
		snprintf(dstid, sizeof(dstid), "%u", NFS_PORT);
	}
	print_nfsaddr(bp2, srcid, dstid);
	(void)printf("%d", length);

	nfsreq_print_noaddr(bp, length, bp2);
	return;

trunc:
	if (!nfserr)
		fputs(" [|nfs]", stdout);
}
