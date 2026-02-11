get_stonith_provider(const char *agent, const char *provider)
{

    if (is_redhat_agent(agent)) {
        return "redhat";

#if HAVE_STONITH_STONITH_H
    } else {
        Stonith *stonith_obj = NULL;

        static gboolean need_init = TRUE;
        static Stonith *(*st_new_fn) (const char *) = NULL;
        static void (*st_del_fn) (Stonith *) = NULL;

        if (need_init) {
            need_init = FALSE;
            st_new_fn =
                find_library_function(&lha_agents_lib, LHA_STONITH_LIBRARY, "stonith_new", FALSE);
            st_del_fn =
                find_library_function(&lha_agents_lib, LHA_STONITH_LIBRARY, "stonith_delete",
                                      FALSE);
        }

        if (lha_agents_lib && st_new_fn && st_del_fn) {
            stonith_obj = (*st_new_fn) (agent);
            if (stonith_obj) {
                (*st_del_fn) (stonith_obj);
                return "heartbeat";
            }
        }
#endif
    }

    crm_err("No such device: %s", agent);
    return NULL;
}
