rename_tag(GSList * filters,
			const gchar * old_tag, const gchar * new_tag)
{
        GSList * action_cur;
        GSList * cur;

	for (cur = filters; cur != NULL; cur = cur->next) {
		FilteringProp   *filtering = (FilteringProp *)cur->data;

                for(action_cur = filtering->action_list ; action_cur != NULL ;
                    action_cur = action_cur->next) {

                        FilteringAction *action = action_cur->data;

                        if (action->type != MATCHACTION_SET_TAG &&
			    action->type != MATCHACTION_UNSET_TAG)
				continue;
                        if (!action->destination)
				continue;
                        if (!strcmp(action->destination, old_tag)) {
				g_free(action->destination);
				action->destination = g_strdup(new_tag);
			}
                }
        }
}
