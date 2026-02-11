gmlc_gui_connexions_evt_btnTlbrEdit_clicked (GtkWidget *widget, gpointer user_data) {
	GmlcGuiConnexions * pGmlcGuiCnxns = GMLC_GUI_CONNEXIONS(user_data);

	pGmlcGuiCnxns->bShowEditPart = (pGmlcGuiCnxns->bShowEditPart) ? FALSE : TRUE ;

	if (pGmlcGuiCnxns->bShowEditPart) {
		gtk_widget_show(GTK_WIDGET(pGmlcGuiCnxns->vbxEditPart));
	} else {
		gtk_widget_hide(GTK_WIDGET(pGmlcGuiCnxns->vbxEditPart));
	}
}
