nfs3_log_rw_call (uint32_t xid, char *op, struct nfs3_fh *fh, offset3 offt,
                  count3 count, int stablewrite)
{
        char    fhstr[1024];

	if (THIS->ctx->log.loglevel < GF_LOG_DEBUG)
		return;
        nfs3_fh_to_str (fh, fhstr);
        if (stablewrite == -1)
                gf_log (GF_NFS3, GF_LOG_DEBUG, "XID: %x, %s: args: %s, offset:"
                        " %"PRIu64",  count: %"PRIu32, xid, op, fhstr, offt,
                        count);
        else
                gf_log (GF_NFS3, GF_LOG_DEBUG, "XID: %x, %s: args: %s, offset:"
                        " %"PRIu64",  count: %"PRIu32", %s", xid, op, fhstr,
                        offt, count,
                        (stablewrite == UNSTABLE)?"UNSTABLE":"STABLE");

}
