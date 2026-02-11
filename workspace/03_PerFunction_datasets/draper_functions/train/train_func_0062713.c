gfxw_remove_id(gfxw_container_t *container, int ID, int subID)
{
	gfxw_widget_t **wp = &(container->contents);

	while (*wp) {
		if ((*wp)->ID == ID
		    && (subID == GFXW_NO_ID
			|| (*wp)->subID == subID)) {
			gfxw_widget_t *widget = *wp;

			*wp = (*wp)->next;
			widget->next = NULL;
			widget->parent = NULL;
			widget->visual = NULL;

			return widget;
		}

		wp = &((*wp)->next);
	}

	return NULL;
}
