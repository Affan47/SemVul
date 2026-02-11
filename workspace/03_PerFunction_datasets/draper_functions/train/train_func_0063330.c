nfs_gfid_dict (inode_t *inode)
{
        uuid_t  newgfid = {0, };
        char    *dyngfid = NULL;
        dict_t  *dictgfid = NULL;
        int     ret = -1;
        uuid_t  rootgfid = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};

        dyngfid = GF_CALLOC (1, sizeof (uuid_t), gf_common_mt_char);
        uuid_generate (newgfid);

        if (uuid_compare (inode->gfid, rootgfid) == 0)
                memcpy (dyngfid, rootgfid, sizeof (uuid_t));
        else
                memcpy (dyngfid, newgfid, sizeof (uuid_t));

        dictgfid = dict_new ();
        if (!dictgfid) {
                gf_log (GF_NFS, GF_LOG_ERROR, "Failed to create gfid dict");
                goto out;
        }

        ret = dict_set_bin (dictgfid, "gfid-req", dyngfid, sizeof (uuid_t));
        if (ret < 0) {
                dict_unref (dictgfid);
                dictgfid = NULL;
        }

out:
        return dictgfid;
}
