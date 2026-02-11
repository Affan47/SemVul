nfs3_fill_fsstat3res (fsstat3res *res, nfsstat3 stat, struct statvfs *fsbuf,
                      struct iatt *postbuf, uint64_t deviceid)
{
        post_op_attr    poa;
        fsstat3resok    resok;

        memset (res, 0, sizeof (*res));
        res->status = stat;
        if (stat != NFS3_OK)
                return;

        nfs3_map_deviceid_to_statdev (postbuf, deviceid);
        poa = nfs3_stat_to_post_op_attr (postbuf);
        resok.tbytes = (size3)(fsbuf->f_frsize * fsbuf->f_blocks);
        resok.fbytes = (size3)(fsbuf->f_frsize * fsbuf->f_bfree);
        resok.abytes = (size3)(fsbuf->f_frsize * fsbuf->f_bavail);
        resok.tfiles = (size3)(fsbuf->f_files);
        resok.ffiles = (size3)(fsbuf->f_ffree);
        resok.afiles = (size3)(fsbuf->f_favail);
        resok.invarsec = 0;

        resok.obj_attributes = poa;
        res->fsstat3res_u.resok = resok;
}
