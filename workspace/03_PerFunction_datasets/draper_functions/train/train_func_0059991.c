nfs3_verify_dircookie (struct nfs3_state *nfs3, fd_t *dirfd, cookie3 cookie,
                       uint64_t cverf, nfsstat3 *stat)
{
        int             ret = -1;

        if ((!nfs3) || (!dirfd))
                return -1;


        if (cookie == 0)
                return 0;

        gf_log (GF_NFS3, GF_LOG_TRACE, "Verifying cookie: cverf: %"PRIu64
                ", cookie: %"PRIu64, cverf, cookie);

        if ((cverf == 0) && (cookie != 0)) {
                gf_log (GF_NFS3, GF_LOG_TRACE, "Bad cookie requested");
                if (stat)
                        *stat = NFS3ERR_BAD_COOKIE;
                goto err;
        }


        gf_log (GF_NFS3, GF_LOG_TRACE, "Cookie verified");
        if (stat)
                *stat = NFS3_OK;
        ret = 0;
err:
        return ret;
}
