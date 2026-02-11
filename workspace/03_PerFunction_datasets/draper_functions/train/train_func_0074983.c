gd_lock_op_phase (struct list_head *peers, glusterd_op_t op, dict_t *op_ctx,
                  char **op_errstr, int npeers)
{
        int                 ret         = -1;
        int                 peer_cnt    = 0;
        uuid_t              peer_uuid   = {0};
        xlator_t            *this       = NULL;
        glusterd_peerinfo_t *peerinfo   = NULL;
        struct syncargs     args        = {0};

        if (!npeers) {
                ret = 0;
                goto out;
        }

        this = THIS;
        synctask_barrier_init((&args));
        peer_cnt = 0;
        list_for_each_entry (peerinfo, peers, op_peers_list) {
                gd_syncop_mgmt_lock (peerinfo->rpc, &args, MY_UUID, peer_uuid);
                peer_cnt++;
        }
        gd_synctask_barrier_wait((&args), peer_cnt);
        ret = args.op_ret;
        if (ret) {
                gf_asprintf (op_errstr, "Another transaction could be "
                             "in progress. Please try again after "
                             "sometime.");
                gf_log (this->name, GF_LOG_ERROR, "Failed to acquire lock");
                goto out;
        }

        ret = 0;
out:
        return ret;
}
