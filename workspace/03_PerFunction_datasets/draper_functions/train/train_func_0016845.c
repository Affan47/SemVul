glusterd_status_volume_brick_rsp (dict_t *rsp_dict, dict_t *op_ctx,
                                  char **op_errstr)
{
        int                             ret = 0;
        glusterd_pr_brick_rsp_conv_t    rsp_ctx = {0};
        int32_t                         count = 0;
        int                             index = 0;

        GF_ASSERT (rsp_dict);
        GF_ASSERT (op_ctx);
        GF_ASSERT (op_errstr);

        ret = dict_get_int32 (op_ctx, "count", &count);
        if (ret) {
                count = 0;
        } else {
                count++;
        }
        ret = dict_get_int32 (rsp_dict, "index", &index);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, "Couldn't get node index");
                goto out;
        }
        dict_del (rsp_dict, "index");

        rsp_ctx.count = index;
        rsp_ctx.dict = op_ctx;
        dict_foreach (rsp_dict, _status_volume_add_brick_rsp, &rsp_ctx);
        ret = dict_set_int32 (op_ctx, "count", count);

out:
        return ret;
}
