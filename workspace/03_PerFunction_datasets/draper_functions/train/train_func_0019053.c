winsync_plugin_call_post_ds_add_group_cb(const Repl_Agmt *ra, const Slapi_Entry *rawentry,
                                         Slapi_Entry *ad_entry, Slapi_Entry *ds_entry, int *result)
{
    WINSYNC_PLUGIN_CALL_PLUGINS_COOKIE_BEGIN(WINSYNC_PLUGIN_POST_DS_ADD_GROUP_CB,winsync_post_add_cb,thefunc)
        (*thefunc)(cookie, rawentry, ad_entry, ds_entry, result);
    WINSYNC_PLUGIN_CALL_PLUGINS_END;

    return;
}
