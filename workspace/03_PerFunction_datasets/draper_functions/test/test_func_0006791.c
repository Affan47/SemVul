unit_select_dialog_popup_main(struct tile *ptile, bool create)
{
  struct unit_select_dialog *pdialog;


  pdialog = usdlg_get(create);


  if (pdialog) {

    gtk_widget_show_all(GTK_WIDGET(pdialog->shell));

    usdlg_tile(pdialog, ptile);

    usdlg_refresh(pdialog);
  }
}
