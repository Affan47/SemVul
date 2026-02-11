process_sipc_cb(fetion_account *ac, const gchar *sipmsg)
{
    gchar              *callid;
    gint                callid0;
    fetion_transaction *trans;
    GSList             *trans_cur;

    if (!(callid = sip_header_get_attr(sipmsg, "I"))) {
        hybrid_debug_error("fetion", "invalid sipc message received\n%s",
                sipmsg);
        g_free(callid);
        return;
    }

    callid0 = atoi(callid);

    trans_cur = ac->trans_list;

    while(trans_cur) {
        trans = (fetion_transaction*)(trans_cur->data);

        if (trans->callid == callid0) {

            if (trans->callback) {
                (trans->callback)(ac, sipmsg, trans);
            }

            transaction_remove(ac, trans);

            break;
        }

        trans_cur = g_slist_next(trans_cur);
    }
}
