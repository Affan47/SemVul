run_action (DhApp *application,
            gboolean is_remote)
{
        if (option_new_window) {
                if (is_remote)
                        dh_app_new_window (application);
        } else if (option_quit) {
                dh_app_quit (application);
        } else if (option_search) {
                dh_app_search (application, option_search);
        } else if (option_search_assistant) {
                dh_app_search_assistant (application, option_search_assistant);
        } else {
                if (is_remote)
                        dh_app_raise (application);
        }
}
