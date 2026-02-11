s_response_triggered(GtkWidget * widget, gint resp, AP_UnixDialog_Replace * dlg)
{
	UT_return_if_fail(widget && dlg);

	if ( resp == BUTTON_FIND )
	  dlg->event_Find();
	else if ( resp == BUTTON_REPLACE)
	  dlg->event_Replace();
	else if ( resp == BUTTON_REPLACE_ALL)
	  dlg->event_ReplaceAll();
	else
	  abiDestroyWidget ( widget ) ;
}
