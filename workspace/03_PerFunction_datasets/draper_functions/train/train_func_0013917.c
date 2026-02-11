connection_check_fields (GstConnectionDialog *dialog)
{
  gboolean active = FALSE;

  if (OOBS_IS_IFACE_WIRELESS (dialog->iface))
    active = (ethernet_dialog_check_fields (dialog) &&
	      wireless_dialog_check_fields (dialog));
  else if (OOBS_IS_IFACE_ETHERNET (dialog->iface) ||
      OOBS_IS_IFACE_IRLAN    (dialog->iface))
    active = ethernet_dialog_check_fields (dialog);
  else if (OOBS_IS_IFACE_PLIP (dialog->iface))
    active = plip_dialog_check_fields (dialog);
  else if (OOBS_IS_IFACE_PPP (dialog->iface))
    active = ppp_dialog_check_fields (dialog);

  gtk_widget_set_sensitive (dialog->ok_button, active);
}
