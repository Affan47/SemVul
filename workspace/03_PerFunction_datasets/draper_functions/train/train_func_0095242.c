show_menu_popup(GtkUIManager *manager, guint button, guint32 time)
{
	GtkWidget *menu = gtk_ui_manager_get_widget (manager, "/MenuGeomMD");
	if (GTK_IS_MENU (menu))
	{
		set_sensitive_option(manager,"/MenuGeomMD/SaveGabedit");
		set_sensitive_option(manager,"/MenuGeomMD/SavePDB");
		set_sensitive_option(manager,"/MenuGeomMD/SaveVelocityAutocorrelation");
		set_sensitive_option(manager,"/MenuGeomMD/DisplayVelocityAutocorrelation");
		set_sensitive_option(manager,"/MenuGeomMD/CreateGaussInput");
		set_sensitive_option(manager,"/MenuGeomMD/CreateGaussInputLink");
		set_sensitive_option(manager,"/MenuGeomMD/CreateGr");
		set_sensitive_option(manager,"/MenuGeomMD/ComputeRMSD");
		set_sensitive_option(manager,"/MenuGeomMD/DeleteGeometry");
		set_sensitive_option(manager,"/MenuGeomMD/DeleteHalfGeometries");
		set_sensitive_option(manager,"/MenuGeomMD/DeleteBeforeSelectedGeometry");
		set_sensitive_option(manager,"/MenuGeomMD/DeleteAfterSelectedGeometry");
		gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL, button, time);
		return TRUE;
	}
	else printf("Erreur menu n'est pas un menu\n");
	return FALSE;
}
