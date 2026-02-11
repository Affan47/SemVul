winsync_plugin_call_pre_ad_search_cb(const Repl_Agmt *ra, const char *agmt_dn,
                                     char **base, int *scope, char **filter,
                                     char ***attrs, LDAPControl ***serverctrls)
{
    WINSYNC_PLUGIN_CALL_PLUGINS_COOKIE_BEGIN(WINSYNC_PLUGIN_PRE_AD_SEARCH_CB,winsync_search_params_cb,thefunc)
        (*thefunc)(cookie, agmt_dn, base, scope, filter, attrs, serverctrls);
    WINSYNC_PLUGIN_CALL_PLUGINS_END;

    return;
}
