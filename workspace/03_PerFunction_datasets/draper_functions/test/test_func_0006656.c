__nfs3_write_resume (nfs3_call_state_t *cs)
{
        int                             ret = -EFAULT;
        nfs_user_t                      nfu = {0, };

        if (!cs)
                return ret;

        nfs_request_user_init (&nfu, cs->req);


        cs->datavec.iov_len = cs->datacount;
        ret = nfs_write (cs->nfsx, cs->vol, &nfu, cs->fd, cs->iobref,
                         &cs->datavec, 1, cs->dataoffset, nfs3svc_write_cbk,
                         cs);

        return ret;
}
