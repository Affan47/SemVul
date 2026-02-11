inner_auth_combo_init (EAPMethodFAST *method,
                       NMConnection *connection,
                       NMSetting8021x *s_8021x,
                       gboolean secrets_only)
{
	EAPMethod *parent = (EAPMethod *) method;
	GtkWidget *combo;
	GtkListStore *auth_model;
	GtkTreeIter iter;
	EAPMethodSimple *em_gtc;
	EAPMethodSimple *em_mschap_v2;
	guint32 active = 0;
	const char *phase2_auth = NULL;

	auth_model = gtk_list_store_new (2, G_TYPE_STRING, eap_method_get_g_type ());

	if (s_8021x) {
		if (nm_setting_802_1x_get_phase2_auth (s_8021x))
			phase2_auth = nm_setting_802_1x_get_phase2_auth (s_8021x);
		else if (nm_setting_802_1x_get_phase2_autheap (s_8021x))
			phase2_auth = nm_setting_802_1x_get_phase2_autheap (s_8021x);
	}

	em_gtc = eap_method_simple_new (method->sec_parent,
	                                connection,
	                                EAP_METHOD_SIMPLE_TYPE_GTC,
	                                TRUE,
	                                method->is_editor,
	                                secrets_only);
	gtk_list_store_append (auth_model, &iter);
	gtk_list_store_set (auth_model, &iter,
	                    I_NAME_COLUMN, _("GTC"),
	                    I_METHOD_COLUMN, em_gtc,
	                    -1);
	eap_method_unref (EAP_METHOD (em_gtc));


	if (phase2_auth && !strcasecmp (phase2_auth, "gtc"))
		active = 0;

	em_mschap_v2 = eap_method_simple_new (method->sec_parent,
	                                      connection,
	                                      EAP_METHOD_SIMPLE_TYPE_MSCHAP_V2,
	                                      TRUE,
	                                      method->is_editor, secrets_only);
	gtk_list_store_append (auth_model, &iter);
	gtk_list_store_set (auth_model, &iter,
	                    I_NAME_COLUMN, _("MSCHAPv2"),
	                    I_METHOD_COLUMN, em_mschap_v2,
	                    -1);
	eap_method_unref (EAP_METHOD (em_mschap_v2));


	if (phase2_auth && !strcasecmp (phase2_auth, "mschapv2"))
		active = 1;

	combo = GTK_WIDGET (gtk_builder_get_object (parent->builder, "eap_fast_inner_auth_combo"));
	g_assert (combo);

	gtk_combo_box_set_model (GTK_COMBO_BOX (combo), GTK_TREE_MODEL (auth_model));
	g_object_unref (G_OBJECT (auth_model));
	gtk_combo_box_set_active (GTK_COMBO_BOX (combo), active);

	g_signal_connect (G_OBJECT (combo), "changed",
	                  (GCallback) inner_auth_combo_changed_cb,
	                  method);
	return combo;
}
