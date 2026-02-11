BuildContextualMenu (gcu::UIManager *UIManager, Object *object, double x, double y)
{
	Object *pAtom = GetAtomAt (x, y);
	if (pAtom)
		return pAtom->BuildContextualMenu (UIManager, object, x, y);
	if (m_Crossing.size () == 0)
		return Object::BuildContextualMenu (UIManager, object, x, y);
	GtkUIManager *uim = static_cast < gcugtk::UIManager * > (UIManager)->GetUIManager ();
	bool is_before = false, is_after = false;
	if (m_Crossing.size () > 0) {
		map<Bond*, BondCrossing>::iterator i, iend = m_Crossing.end ();
		for (i = m_Crossing.begin (); i != iend; i++) {
			if (m_level == (*i).first->m_level || m_type != (*i).first->m_type)
				continue;
			if ((*i).second.is_before)
				is_before = true;
			else
				is_after = true;
		}
	}
	if (!(is_before || is_after))
		return Object::BuildContextualMenu (UIManager, object, x, y);
	GtkActionGroup *group = gtk_action_group_new ("bond");
	GtkAction *action;
	action = gtk_action_new ("Bond", _("Bond"), NULL, NULL);
	gtk_action_group_add_action (group, action);
	g_object_unref (action);
	if (is_before) {
		action = gtk_action_new ("MoveBack", _("Move to back"), NULL, NULL);
		g_signal_connect_swapped (action, "activate", G_CALLBACK (on_move_to_back), this);
		gtk_action_group_add_action (group, action);
		g_object_unref (action);
		gtk_ui_manager_add_ui_from_string (uim, "<ui><popup><menu action='Bond'><menuitem action='MoveBack'/></menu></popup></ui>", -1, NULL);
	}
	if (is_after) {
		action = gtk_action_new ("BringFront", _("Bring to front"), NULL, NULL);
		g_signal_connect_swapped (action, "activate", G_CALLBACK (on_bring_to_front), this);
		gtk_action_group_add_action (group, action);
		g_object_unref (action);
		gtk_ui_manager_add_ui_from_string (uim, "<ui><popup><menu action='Bond'><menuitem action='BringFront'/></menu></popup></ui>", -1, NULL);
	}
	gtk_ui_manager_insert_action_group (uim, group, 0);
	g_object_unref (group);
	Object::BuildContextualMenu (UIManager, object, x, y);
	return true;
}
