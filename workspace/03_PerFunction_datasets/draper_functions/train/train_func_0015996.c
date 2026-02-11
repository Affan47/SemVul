glusterd_store_volinfo_brick_fname_write (int vol_fd,
                                         glusterd_brickinfo_t *brickinfo,
                                         int32_t brick_count)
{
        char                    key[PATH_MAX] = {0,};
        char                    brickfname[PATH_MAX] = {0,};
        int32_t                 ret = -1;

        snprintf (key, sizeof (key), "%s-%d", GLUSTERD_STORE_KEY_VOL_BRICK,
                  brick_count);
        glusterd_store_brickinfofname_set (brickinfo, brickfname,
                                        sizeof (brickfname));
        ret = gf_store_save_value (vol_fd, key, brickfname);
        if (ret)
                goto out;

out:
        return ret;
}
