s_dlg_response ( GtkWidget * widget, gint id,
							 XAP_UnixDialog_Insert_Symbol * dlg )
{
	UT_return_if_fail(widget && dlg);

	switch ( id )
	  {
	  case XAP_UnixDialog_Insert_Symbol::BUTTON_INSERT:
		  dlg->event_Insert();
		  break;

	  case XAP_UnixDialog_Insert_Symbol::BUTTON_CLOSE:
		  abiDestroyWidget(widget);
		  break;
	  }
}
