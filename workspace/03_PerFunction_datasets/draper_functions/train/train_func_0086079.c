compose_put_existing_to_front(MsgInfo *info)
{
	GList *compose_list = compose_get_compose_list();
	GList *elem = NULL;

	if (compose_list) {
		for (elem = compose_list; elem != NULL && elem->data != NULL;
		     elem = elem->next) {
			Compose *c = (Compose*)elem->data;

			if (!c->targetinfo || !c->targetinfo->msgid ||
			    !info->msgid)
			    	continue;

			if (!strcmp(c->targetinfo->msgid, info->msgid)) {
				gtkut_window_popup(c->window);
				return TRUE;
			}
		}
	}
	return FALSE;
}
