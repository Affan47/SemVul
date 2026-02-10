dialog_delete_callback (GtkWidget *widget,
			GdkEvent  *event,
			gpointer   data)
{
  StpuiBasicCallback cancel_callback;
  GtkWidget     *cancel_widget;

  cancel_callback =
    (StpuiBasicCallback) g_object_get_data (G_OBJECT (widget),
					    "dialog_cancel_callback");
  cancel_widget =
    (GtkWidget*) g_object_get_data (G_OBJECT (widget),
				    "dialog_cancel_widget");


  if (cancel_callback)
    (* cancel_callback) (G_OBJECT(cancel_widget), data);

  return TRUE;
}
