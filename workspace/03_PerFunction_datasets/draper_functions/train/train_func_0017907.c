nfs3_log_write_res (uint32_t xid, nfsstat3 stat, int pstat, count3 count,
                    int stable, uint64_t wverf)
{
        char    errstr[1024];
	int	ll = nfs3_loglevel (NFS3_WRITE, stat);

	if (gf_log_loglevel < ll)
		return;

        nfs3_stat_to_errstr (xid, "WRITE", stat, pstat, errstr);
        gf_log (GF_NFS3, ll, "%s, count: %"PRIu32", %s,wverf: %"PRIu64
                , errstr, count, (stable == UNSTABLE)?"UNSTABLE":"STABLE",
                wverf);
}
