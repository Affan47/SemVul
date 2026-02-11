glusterd_store_volinfo_write (int fd, glusterd_volinfo_t *volinfo)
{
        int32_t                         ret = -1;
        gf_store_handle_t              *shandle = NULL;
        GF_ASSERT (fd > 0);
        GF_ASSERT (volinfo);
        GF_ASSERT (volinfo->shandle);

        shandle = volinfo->shandle;
        ret = glusterd_volume_exclude_options_write (fd, volinfo);
        if (ret)
                goto out;

        shandle->fd = fd;
        dict_foreach (volinfo->dict, _storeopts, shandle);

        dict_foreach (volinfo->gsync_slaves, _storeslaves, shandle);
        shandle->fd = 0;
out:
        gf_log (THIS->name, GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
