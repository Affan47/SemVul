prefs_filtering_action_ok(void)
{
        GSList * action_list;
        GSList * cur;

	action_list = prefs_filtering_action_get_list();

        if (action_list == NULL) {
                alertpanel_error(_("No action was defined."));
                return;
        }

        if (filtering_action_callback != NULL)
                filtering_action_callback(action_list);
        for(cur = action_list ; cur != NULL ; cur = cur->next) {
                filteringaction_free(cur->data);
        }
        g_slist_free(action_list);

	gtk_widget_destroy(filtering_action.window);
	filtering_action.window = NULL;
        inc_unlock();
}
