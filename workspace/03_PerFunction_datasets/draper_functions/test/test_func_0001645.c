gpl_dialog_selected(GtkWidget* widget_p, void* data) {
  GplDialog* instance_p = static_cast<GplDialog*>(data);
  gtk_widget_hide(GTK_WIDGET(instance_p->get_win()));
  if (widget_p == instance_p->accept_button_p) instance_p->result = GplDialog::accepted;
  else if (widget_p == instance_p->reject_button_p) instance_p->result = GplDialog::rejected;
  else write_error("Callback error in GplDialogCB::gpl_dialog_selected()\n");
  instance_p->close();
}
