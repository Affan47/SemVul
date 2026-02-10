glusterd_volume_compute_cksum (glusterd_volinfo_t  *volinfo)
{
        int32_t                 ret = -1;
        glusterd_conf_t         *priv = NULL;
        char                    path[PATH_MAX] = {0,};
        char                    cksum_path[PATH_MAX] = {0,};
        char                    filepath[PATH_MAX] = {0,};
        int                     fd = -1;
        uint32_t                cksum = 0;
        char                    buf[4096] = {0,};
        char                    sort_filepath[PATH_MAX] = {0};
        gf_boolean_t            unlink_sortfile = _gf_false;
        int                     sort_fd = 0;
        runner_t                runner;

        GF_ASSERT (volinfo);

        priv = THIS->private;
        GF_ASSERT (priv);

        GLUSTERD_GET_VOLUME_DIR (path, volinfo, priv);

        snprintf (cksum_path, sizeof (cksum_path), "%s/%s",
                  path, GLUSTERD_CKSUM_FILE);

        fd = open (cksum_path, O_RDWR | O_APPEND | O_CREAT| O_TRUNC, 0644);

        if (-1 == fd) {
                gf_log (THIS->name, GF_LOG_ERROR, "Unable to open %s, errno: %d",
                        cksum_path, errno);
                ret = -1;
                goto out;
        }

        snprintf (filepath, sizeof (filepath), "%s/%s", path,
                  GLUSTERD_VOLUME_INFO_FILE);
        snprintf (sort_filepath, sizeof (sort_filepath), "/tmp/%s.XXXXXX",
                  volinfo->volname);
        sort_fd = mkstemp (sort_filepath);
        if (sort_fd < 0) {
                gf_log (THIS->name, GF_LOG_ERROR, "Could not generate temp file, "
                        "reason: %s for volume: %s", strerror (errno),
                        volinfo->volname);
                goto out;
        } else {
                unlink_sortfile = _gf_true;
        }


        runinit (&runner);
        runner_add_args (&runner, "sort", filepath, NULL);
        runner_redir (&runner, STDOUT_FILENO, sort_fd);

        ret = runner_run (&runner);
        close (sort_fd);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, "failed to sort file %s to %s",
                        filepath, sort_filepath);
                goto out;
        }
        ret = get_checksum_for_path (sort_filepath, &cksum);

        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, "Unable to get checksum"
                        " for path: %s", sort_filepath);
                goto out;
        }

        snprintf (buf, sizeof (buf), "%s=%u\n", "info", cksum);
        ret = write (fd, buf, strlen (buf));

        if (ret <= 0) {
                ret = -1;
                goto out;
        }

        ret = get_checksum_for_file (fd, &cksum);

        if (ret)
                goto out;

        volinfo->cksum = cksum;

out:
        if (fd > 0)
               close (fd);
        if (unlink_sortfile)
               unlink (sort_filepath);
        gf_log (THIS->name, GF_LOG_DEBUG, "Returning with %d", ret);

        return ret;
}
