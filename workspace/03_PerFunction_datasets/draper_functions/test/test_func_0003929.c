eel_editable_label_set_line_wrap_mode (EelEditableLabel *label,
				       PangoWrapMode     mode)
{
  g_return_if_fail (EEL_IS_EDITABLE_LABEL (label));

  if (label->wrap_mode != mode)
    {
      label->wrap_mode = mode;

      gtk_widget_queue_resize (GTK_WIDGET (label));
    }

}
