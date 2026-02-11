netsnmp_callback_open(int attach_to,
                      int (*return_func) (int op,
                                          netsnmp_session * session,
                                          int reqid, netsnmp_pdu *pdu,
                                          void *magic),
                      int (*fpre_parse) (netsnmp_session *,
                                         struct netsnmp_transport_s *,
                                         void *, int),
                      int (*fpost_parse) (netsnmp_session *, netsnmp_pdu *,
                                          int))
{
    netsnmp_session callback_sess, *callback_ss;
    netsnmp_transport *callback_tr;

    callback_tr = netsnmp_callback_transport(attach_to);
    snmp_sess_init(&callback_sess);
    callback_sess.callback = return_func;
    if (attach_to) {


    } else {
        callback_sess.isAuthoritative = SNMP_SESS_AUTHORITATIVE;
    }
    callback_sess.remote_port = 0;
    callback_sess.retries = 0;
    callback_sess.timeout = 30000000;
    callback_sess.version = SNMP_DEFAULT_VERSION;
    callback_ss = snmp_add_full(&callback_sess, callback_tr,
                                fpre_parse,
                                netsnmp_callback_hook_parse, fpost_parse,
                                netsnmp_callback_hook_build,
                                NULL,
                                netsnmp_callback_check_packet,
                                netsnmp_callback_create_pdu);
    if (callback_ss)
        callback_ss->local_port =
            ((netsnmp_callback_info *) callback_tr->data)->callback_num;
    return callback_ss;
}
