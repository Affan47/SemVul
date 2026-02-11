gf_cli_gsync_set_cbk (struct rpc_req *req, struct iovec *iov,
                         int count, void *myframe)
{
        int                     ret     = -1;
        gf_cli_rsp              rsp     = {0, };
        dict_t                  *dict   = NULL;
        char                    *gsync_status = NULL;
        char                    *master = NULL;
        char                    *slave  = NULL;
        int32_t                  type    = 0;

        if (req->rpc_status == -1) {
                ret = -1;
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp, (xdrproc_t)xdr_gf_cli_rsp);
        if (ret < 0) {
                gf_log ("", GF_LOG_ERROR,
                        "Unable to get response structure");
                goto out;
        }

        dict = dict_new ();

        if (!dict) {
                ret = -1;
                goto out;
        }

        ret = dict_unserialize (rsp.dict.dict_val, rsp.dict.dict_len, &dict);

        if (ret)
                goto out;

        if (global_state->mode & GLUSTER_MODE_XML) {
                ret = cli_xml_output_vol_gsync (dict, rsp.op_ret, rsp.op_errno,
                                                rsp.op_errstr);
                if (ret)
                        gf_log ("cli", GF_LOG_ERROR,
                                "Error outputting to xml");
                goto out;
        }

        if (rsp.op_ret) {
                cli_err ("%s", rsp.op_errstr ? rsp.op_errstr :
                         GEOREP" command unsuccessful");
                ret = rsp.op_ret;
                goto out;
        }

        ret = dict_get_str (dict, "gsync-status", &gsync_status);
        if (!ret)
                cli_out ("%s", gsync_status);
        else
                ret = 0;

        ret = dict_get_int32 (dict, "type", &type);
        if (ret) {
                gf_log (THIS->name, GF_LOG_ERROR, "failed to get type");
                goto out;
        }

        switch (type) {
                case GF_GSYNC_OPTION_TYPE_START:
                case GF_GSYNC_OPTION_TYPE_STOP:
                        if (dict_get_str (dict, "master", &master) != 0)
                                master = "???";
                        if (dict_get_str (dict, "slave", &slave) != 0)
                                slave = "???";

                        cli_out ("%s " GEOREP " session between %s & %s"
                                 " has been successful",
                                 type == GF_GSYNC_OPTION_TYPE_START ?
                                  "Starting" : "Stopping",
                                 master, slave);
                break;

                case GF_GSYNC_OPTION_TYPE_CONFIG:
                        ret = gf_cli_gsync_config_command (dict);
                break;

                case GF_GSYNC_OPTION_TYPE_STATUS:
                        ret = gf_cli_gsync_out_status (dict);
                        goto out;
                default:
                        cli_out (GEOREP" command executed successfully");
        }

out:
        if (dict)
                dict_unref (dict);
        cli_cmd_broadcast_response (ret);

        free (rsp.dict.dict_val);

        return ret;
}
