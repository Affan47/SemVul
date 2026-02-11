nfs3_log_readdirp_res (uint32_t xid, nfsstat3 stat, int pstat, uint64_t cverf,
                       count3 dircount, count3 maxcount, int is_eof)
{
        char    errstr[1024];
	int	ll = nfs3_loglevel (NFS3_READDIRP, stat);

	if (THIS->ctx->log.loglevel < ll)
		return;
        nfs3_stat_to_errstr (xid, "READDIRPLUS", stat, pstat, errstr);
        gf_log (GF_NFS3, ll, "%s, dircount: %"PRIu32", maxcount: %"
                PRIu32", cverf: %"PRIu64", is_eof: %d", errstr, dircount,
                maxcount, cverf, is_eof);
}
