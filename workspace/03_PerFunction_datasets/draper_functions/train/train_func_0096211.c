gd_commit_op_phase (struct list_head *peers, glusterd_op_t op, dict_t *op_ctx,
                    dict_t *req_dict, char **op_errstr, int npeers)
{
        dict_t                      *rsp_dict       = NULL;
        int                         peer_cnt        = -1;
        int                         ret             = -1;
        char                        *hostname       = NULL;
        glusterd_peerinfo_t         *peerinfo       = NULL;
        xlator_t                    *this           = NULL;
        uuid_t                      tmp_uuid        = {0};
        char                        *errstr         = NULL;
        struct syncargs             args            = {0};

        this = THIS;
        rsp_dict = dict_new ();
        if (!rsp_dict) {
                ret = -1;
                goto out;
        }

        ret = glusterd_op_commit_perform (op, req_dict, op_errstr, rsp_dict);
        if (ret) {
                hostname = "localhost";
                goto commit_done;
        }
        if (op != GD_OP_SYNC_VOLUME) {
                ret =  glusterd_syncop_aggr_rsp_dict (op, op_ctx, rsp_dict);
                if (ret) {
                        gf_log (this->name, GF_LOG_ERROR, "%s",
                                "Failed to aggregate response "
                                "from node/brick");
                        goto out;
                }
        }
        dict_unref (rsp_dict);
        rsp_dict = NULL;

commit_done:
        if (ret) {
                gf_log (this->name, GF_LOG_ERROR, LOGSTR_COMMIT_FAIL,
                        gd_op_list[op], hostname, (*op_errstr) ? ":" : " ",
                        (*op_errstr) ? *op_errstr : " ");
                if (*op_errstr == NULL)
                        gf_asprintf (op_errstr, OPERRSTR_COMMIT_FAIL,
                                     hostname);
                goto out;
        }

        if (!npeers) {
                ret = 0;
                goto out;
        }
        gd_syncargs_init (&args, op_ctx);
        synctask_barrier_init((&args));
        peer_cnt = 0;
        list_for_each_entry (peerinfo, peers, op_peers_list) {
                ret = gd_syncop_mgmt_commit_op (peerinfo->rpc, &args,
                                                MY_UUID, tmp_uuid,
                                                op, req_dict, op_ctx);
                peer_cnt++;
        }
        gd_synctask_barrier_wait((&args), peer_cnt);
        ret = args.op_ret;
        if (dict_get_str (op_ctx, "errstr", &errstr) == 0)
                *op_errstr = gf_strdup (errstr);

out:
        if (!ret)
                glusterd_op_modify_op_ctx (op, op_ctx);

        if (rsp_dict)
                dict_unref (rsp_dict);
        return ret;
}
