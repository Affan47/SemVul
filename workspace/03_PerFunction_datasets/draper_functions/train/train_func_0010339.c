glusterd_append_status_dicts (dict_t *dst, dict_t *src)
{
        int              dst_count = 0;
        int              src_count = 0;
        int              i = 0;
        int              ret = 0;
        char             mst[PATH_MAX] = {0,};
        char             slv[PATH_MAX] = {0, };
        char             sts[PATH_MAX] = {0, };
        char             *mst_val = NULL;
        char             *slv_val = NULL;
        char             *sts_val = NULL;

        GF_ASSERT (dst);

        if (src == NULL)
                goto out;

        ret = dict_get_int32 (dst, "gsync-count", &dst_count);
        if (ret)
                dst_count = 0;

        ret = dict_get_int32 (src, "gsync-count", &src_count);
        if (ret || !src_count) {
                gf_log ("", GF_LOG_DEBUG, "Source brick empty");
                ret = 0;
                goto out;
        }

        for (i = 1; i <= src_count; i++) {
                snprintf (mst, sizeof(mst), "master%d", i);
                snprintf (slv, sizeof(slv), "slave%d", i);
                snprintf (sts, sizeof(sts), "status%d", i);

                ret = dict_get_str (src, mst, &mst_val);
                if (ret)
                        goto out;

                ret = dict_get_str (src, slv, &slv_val);
                if (ret)
                        goto out;

                ret = dict_get_str (src, sts, &sts_val);
                if (ret)
                        goto out;

                snprintf (mst, sizeof(mst), "master%d", i+dst_count);
                snprintf (slv, sizeof(slv), "slave%d", i+dst_count);
                snprintf (sts, sizeof(sts), "status%d", i+dst_count);

                ret = dict_set_dynstr (dst, mst, gf_strdup (mst_val));
                if (ret)
                        goto out;

                ret = dict_set_dynstr (dst, slv, gf_strdup (slv_val));
                if (ret)
                        goto out;

                ret = dict_set_dynstr (dst, sts, gf_strdup (sts_val));
                if (ret)
                        goto out;

        }

        ret = dict_set_int32 (dst, "gsync-count", dst_count+src_count);

 out:
        gf_log ("", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;

}
