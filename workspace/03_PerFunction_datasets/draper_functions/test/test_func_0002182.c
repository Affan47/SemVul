main_window_structure_construct (GType object_type, GtkUIManager* ui_manager) {
	MainWindowStructure* self = NULL;
	GtkUIManager* _tmp0_ = NULL;
	GtkUIManager* _tmp1_ = NULL;
	GtkActionGroup* action_group = NULL;
	GtkActionGroup* _tmp2_ = NULL;
	GtkUIManager* _tmp3_ = NULL;
	g_return_val_if_fail (ui_manager != NULL, NULL);
	self = (MainWindowStructure*) g_type_create_instance (object_type);
	_tmp0_ = ui_manager;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->priv->_ui_manager);
	self->priv->_ui_manager = _tmp1_;
	_tmp2_ = gtk_action_group_new ("StructureActionGroup");
	action_group = _tmp2_;
	gtk_action_group_set_translation_domain (action_group, GETTEXT_PACKAGE);
	gtk_action_group_add_actions (action_group, MAIN_WINDOW_STRUCTURE__action_entries, G_N_ELEMENTS (MAIN_WINDOW_STRUCTURE__action_entries), self);
	_tmp3_ = ui_manager;
	gtk_ui_manager_insert_action_group (_tmp3_, action_group, 0);
	_g_object_unref0 (action_group);
	return self;
}
