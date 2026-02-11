nfs3_fill_rename3res (rename3res *res, nfsstat3 stat, struct iatt *buf,
                      struct iatt *preoldparent, struct iatt *postoldparent,
                      struct iatt *prenewparent, struct iatt *postnewparent,
                      uint64_t deviceid)

{
        wcc_data        dirwcc;

        memset (res, 0, sizeof (*res));
        res->status = stat;
        if (stat != NFS3_OK)
                return;

        nfs3_map_deviceid_to_statdev (preoldparent, deviceid);
        nfs3_map_deviceid_to_statdev (postoldparent, deviceid);
        nfs3_map_deviceid_to_statdev (prenewparent, deviceid);
        nfs3_map_deviceid_to_statdev (postnewparent, deviceid);
        nfs3_map_deviceid_to_statdev (buf, deviceid);
        dirwcc = nfs3_stat_to_wcc_data (preoldparent, postoldparent);
        res->rename3res_u.resok.fromdir_wcc = dirwcc;
        dirwcc = nfs3_stat_to_wcc_data (prenewparent, postnewparent);
        res->rename3res_u.resok.todir_wcc = dirwcc;
}
