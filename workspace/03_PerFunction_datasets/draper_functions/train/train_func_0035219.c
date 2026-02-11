nfs3_create_exclusive (nfs3_call_state_t *cs)
{
        int                     ret = -EFAULT;
        nfs_user_t              nfu = {0, };

        if (!cs)
                return ret;


        memcpy (&cs->stbuf.ia_atime, &cs->cookieverf,
                sizeof (cs->stbuf.ia_atime));
        memcpy (&cs->stbuf.ia_mtime,
                ((char *) &cs->cookieverf) + sizeof (cs->stbuf.ia_atime),
                sizeof (cs->stbuf.ia_mtime));
        cs->setattr_valid |= GF_SET_ATTR_ATIME;
        cs->setattr_valid |= GF_SET_ATTR_MTIME;
        nfs_request_user_init (&nfu, cs->req);


        if ((cs->resolve_ret == 0) ||
            ((cs->resolve_ret == -1) && (cs->resolve_errno != ENOENT))) {
                ret = nfs_stat (cs->nfsx, cs->vol, &nfu, &cs->resolvedloc,
                                nfs3svc_create_stat_cbk, cs);
                goto nfs3err;
        }

        if (cs->setattr_valid & GF_SET_ATTR_MODE) {
                cs->setattr_valid &= ~GF_SET_ATTR_MODE;
                ret = nfs_create (cs->nfsx, cs->vol, &nfu, &cs->resolvedloc,
                                  O_RDWR, cs->mode, nfs3svc_create_cbk, cs);
        } else
                ret = nfs_create (cs->nfsx, cs->vol, &nfu, &cs->resolvedloc,
                                  O_RDWR,
                                  NFS_DEFAULT_CREATE_MODE, nfs3svc_create_cbk,
                                  cs);

nfs3err:
        return ret;
}
