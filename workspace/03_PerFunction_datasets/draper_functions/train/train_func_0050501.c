gf_cli3_1_uuid_get (call_frame_t *frame, xlator_t *this,
                      void *data)
{
        gf_cli_req                      req = {{0,}};
        int                             ret = 0;
        dict_t                          *dict = NULL;

        if (!frame || !this || !data) {
                ret = -1;
                goto out;
        }

        dict = data;
        ret = cli_to_glusterd (&req, frame, gf_cli3_1_uuid_get_cbk,
                               (xdrproc_t)xdr_gf_cli_req, dict,
                               GLUSTER_CLI_UUID_GET, this, cli_rpc_prog,
                               NULL);
out:
        gf_log ("cli", GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
