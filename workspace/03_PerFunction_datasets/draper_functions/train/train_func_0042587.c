glusterd_peer_destroy (glusterd_peerinfo_t *peerinfo)
{
        int32_t                         ret = -1;

        if (!peerinfo)
                goto out;

        ret = glusterd_store_delete_peerinfo (peerinfo);

        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Deleting peer info failed");
        }

        list_del_init (&peerinfo->uuid_list);
        GF_FREE (peerinfo->hostname);
        glusterd_sm_tr_log_delete (&peerinfo->sm_log);
        GF_FREE (peerinfo);
        peerinfo = NULL;

        ret = 0;

out:
        return ret;
}
