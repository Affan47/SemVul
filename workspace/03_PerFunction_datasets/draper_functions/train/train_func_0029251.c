set_color_options(void)
{
  stp_parameter_t desc;
  stp_describe_parameter(pv->v, "PrintingMode", &desc);
  if (desc.p_type == STP_PARAMETER_TYPE_STRING_LIST)
    {
      if (!stp_string_list_is_present(desc.bounds.str, "Color"))
	{
	  gtk_widget_set_sensitive (output_types[1].button, TRUE);
	  if (gtk_toggle_button_get_active
	      (GTK_TOGGLE_BUTTON (output_types[0].button)) == TRUE)
	    gtk_toggle_button_set_active
	      (GTK_TOGGLE_BUTTON (output_types[1].button), TRUE);
	  gtk_widget_set_sensitive (output_types[0].button, FALSE);
	}
      else if (!stp_string_list_is_present(desc.bounds.str, "BW"))
	{
	  gtk_widget_set_sensitive (output_types[0].button, TRUE);
	  if (gtk_toggle_button_get_active
	      (GTK_TOGGLE_BUTTON (output_types[1].button)) == TRUE)
	    gtk_toggle_button_set_active
	      (GTK_TOGGLE_BUTTON (output_types[0].button), TRUE);
	  gtk_widget_set_sensitive (output_types[1].button, FALSE);
	}
      else
	{
	  gtk_widget_set_sensitive (output_types[0].button, TRUE);
	  gtk_widget_set_sensitive (output_types[1].button, TRUE);
	}
    }
  stp_parameter_description_destroy(&desc);
}
