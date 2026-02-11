mca_oob_tcp_component_hop_unknown(int fd, short args, void *cbdata)
{
    mca_oob_tcp_msg_error_t *mop = (mca_oob_tcp_msg_error_t*)cbdata;
    mca_oob_tcp_module_t *mod;
    uint64_t ui64;
    int k;
    mca_oob_tcp_component_peer_t *pr;
    orte_rml_send_t *snd;

    opal_output_verbose(OOB_TCP_DEBUG_CONNECT, orte_oob_base_framework.framework_output,
                        "%s tcp:unknown hop called for peer %s on interface %s",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                        ORTE_NAME_PRINT(&mop->hop),
                        mop->mod->if_name);

    if (orte_finalizing || orte_abnormal_term_ordered) {

        OBJ_RELEASE(mop);
        return;
    }


    memcpy(&ui64, (char*)&(mop->hop), sizeof(uint64_t));


    if (OPAL_SUCCESS != opal_hash_table_get_value_uint64(&mca_oob_tcp_component.peers,
                                                         ui64, (void**)&pr) || NULL == pr) {

        goto cleanup;

    }


    opal_bitmap_clear_bit(&pr->reachable, mop->mod->if_kidx);


    for (k=0; k < mca_oob_tcp_component.modules.size; k++) {
        if (NULL == (mod = (mca_oob_tcp_module_t*)opal_pointer_array_get_item(&mca_oob_tcp_component.modules, k))) {
            continue;
        }
        if (opal_bitmap_is_set_bit(&pr->reachable, k)) {

            opal_output_verbose(OOB_TCP_DEBUG_CONNECT, orte_oob_base_framework.framework_output,
                                "%s tcp:unknown hop attempting send to peer %s via interface %s",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                ORTE_NAME_PRINT(&mop->hop), mod->if_name);
            mod->api.resend((struct mca_oob_tcp_msg_error_t*)mop);
            OBJ_RELEASE(mop);
            return;
        }
    }

 cleanup:


    MCA_OOB_TCP_HDR_NTOH(&mop->snd->hdr);
    snd = OBJ_NEW(orte_rml_send_t);
    snd->dst = mop->snd->hdr.dst;
    snd->origin = mop->snd->hdr.origin;
    snd->tag = mop->snd->hdr.tag;
    snd->data = mop->snd->data;
    snd->count = mop->snd->hdr.nbytes;
    snd->cbfunc.iov = NULL;
    snd->cbdata = NULL;

    ORTE_OOB_SEND(snd);

    mop->snd->data = NULL;

    OBJ_RELEASE(mop);
}
