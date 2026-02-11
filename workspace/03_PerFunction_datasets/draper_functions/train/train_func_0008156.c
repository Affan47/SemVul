winsync_plugin_call_pre_ad_mod_user_cb(const Repl_Agmt *ra, const Slapi_Entry *rawentry,
                                       Slapi_Entry *ad_entry, Slapi_Entry *ds_entry,
                                       Slapi_Mods *smods, int *do_modify)
{
    WINSYNC_PLUGIN_CALL_PLUGINS_COOKIE_BEGIN(WINSYNC_PLUGIN_PRE_AD_MOD_USER_CB,winsync_pre_mod_cb,thefunc)
        (*thefunc)(cookie, rawentry, ad_entry, ds_entry, smods, do_modify);
    WINSYNC_PLUGIN_CALL_PLUGINS_END;

    return;
}
