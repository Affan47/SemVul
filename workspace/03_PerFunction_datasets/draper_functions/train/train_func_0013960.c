pic_code_ok_cb(HybridAccount *account, const gchar *code, gpointer user_data)
{
    fetion_account *ac = (fetion_account*)user_data;

    hybrid_debug_info("fetion", "pic code %s inputed.", code);

    g_free(ac->verification->code);
    ac->verification->code = g_strdup(code);

    if (VERIFY_TYPE_SSI == verify_data.type) {
        hybrid_ssl_connect(SSI_SERVER, 443, ssi_auth_action, ac);

    } else {
        printf("%s\n", verify_data.response);
        sipc_aut_action(verify_data.sipc_conn, ac, verify_data.response);
    }
}
