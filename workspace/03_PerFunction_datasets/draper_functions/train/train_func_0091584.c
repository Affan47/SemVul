glusterd_build_volume_dict (dict_t **vols)
{
        int32_t                 ret = -1;
        dict_t                  *dict = NULL;
        glusterd_conf_t         *priv = NULL;
        glusterd_volinfo_t      *volinfo = NULL;
        int32_t                 count = 0;
        glusterd_dict_ctx_t     ctx            = {0};

        priv = THIS->private;

        dict = dict_new ();

        if (!dict)
                goto out;

        list_for_each_entry (volinfo, &priv->volumes, vol_list) {
                count++;
                ret = glusterd_add_volume_to_dict (volinfo, dict, count);
                if (ret)
                        goto out;
        }


        ret = dict_set_int32 (dict, "count", count);
        if (ret)
                goto out;

        ctx.dict = dict;
        ctx.prefix = "global";
        ctx.opt_count = 1;
        ctx.key_name = "key";
        ctx.val_name = "val";
        dict_foreach (priv->opts, _add_dict_to_prdict, &ctx);
        ctx.opt_count--;
        ret = dict_set_int32 (dict, "global-opt-count", ctx.opt_count);
        if (ret)
                goto out;

        *vols = dict;
out:
        gf_log ("", GF_LOG_DEBUG, "Returning with %d", ret);
        if (ret)
                dict_unref (dict);

        return ret;
}
