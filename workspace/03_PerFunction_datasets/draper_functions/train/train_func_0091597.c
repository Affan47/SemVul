do_all_updates(void)
{
  gint i;
  suppress_preview_update++;
  set_orientation(pv->orientation);
  invalidate_preview_thumbnail ();
  preview_update ();
  update_standard_print_command();

  if (pv->scaling < 0)
    {
      gdouble tmp = -pv->scaling;
      gdouble max_ppi_scaling;
      gdouble min_ppi_scaling;

      compute_scaling_limits(&min_ppi_scaling, &max_ppi_scaling);

      gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (scaling_ppi), TRUE);
      GTK_ADJUSTMENT (scaling_adjustment)->lower = min_ppi_scaling;
      GTK_ADJUSTMENT (scaling_adjustment)->upper = max_ppi_scaling;
      GTK_ADJUSTMENT (scaling_adjustment)->value = tmp;
      gtk_adjustment_changed (GTK_ADJUSTMENT (scaling_adjustment));
      gtk_adjustment_value_changed (GTK_ADJUSTMENT (scaling_adjustment));
    }
  else
    {
      gdouble tmp = pv->scaling;

      gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (scaling_percent), TRUE);
      GTK_ADJUSTMENT (scaling_adjustment)->lower = minimum_image_percent;
      GTK_ADJUSTMENT (scaling_adjustment)->upper = 100.0;
      GTK_ADJUSTMENT (scaling_adjustment)->value = tmp;
      g_signal_emit_by_name (G_OBJECT(scaling_adjustment), "changed");
      g_signal_emit_by_name (G_OBJECT(scaling_adjustment), "value_changed");
    }

  set_color_options();
  for (i = 0; i < output_type_count; i++)
    {
      if (stp_get_string_parameter(pv->v, "PrintingMode") &&
	  strcmp(output_types[i].value,
		 stp_get_string_parameter(pv->v, "PrintingMode")) == 0)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(output_types[i].button),
				     TRUE);
    }


  update_options();
  do_color_updates ();

  gtk_option_menu_set_history (GTK_OPTION_MENU (orientation_menu),
			       pv->orientation + 1);

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(units[pv->unit].checkbox),
			       TRUE);
  gtk_label_set_text(GTK_LABEL(units_label), units[pv->unit].name);
  suppress_preview_update--;
  preview_update ();
}
