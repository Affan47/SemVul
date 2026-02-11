cd_size_page_prepare_cb (glTemplateDesigner *dialog)
{
	gdouble max_w, max_h;
	gdouble radius, hole, w, h, waste, margin;


	max_w = gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->pg_w_spin));
	max_h = gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->pg_h_spin));

	radius = gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->cd_radius_spin));
	hole = gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->cd_hole_spin));
	w = gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->cd_w_spin));
	h = gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->cd_h_spin));
	waste  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->cd_waste_spin));
	margin = gtk_spin_button_get_value (GTK_SPIN_BUTTON(dialog->priv->cd_margin_spin));

	gtk_spin_button_set_range (GTK_SPIN_BUTTON (dialog->priv->cd_radius_spin),
                                   dialog->priv->climb_rate, MIN(max_w, max_h)/2.0);
	gtk_spin_button_set_range (GTK_SPIN_BUTTON (dialog->priv->cd_hole_spin),
                                   dialog->priv->climb_rate, MIN(max_w, max_h)/2.0);
	gtk_spin_button_set_range (GTK_SPIN_BUTTON (dialog->priv->cd_w_spin),
                                   0.0, max_w);
	gtk_spin_button_set_range (GTK_SPIN_BUTTON (dialog->priv->cd_h_spin),
                                   0.0, max_h);
	gtk_spin_button_set_range (GTK_SPIN_BUTTON (dialog->priv->cd_waste_spin),
                                   0.0, MIN(max_w, max_h)/4.0);
	gtk_spin_button_set_range (GTK_SPIN_BUTTON (dialog->priv->cd_margin_spin),
                                   0.0, MIN(max_w, max_h)/4.0);

	gtk_spin_button_set_value (GTK_SPIN_BUTTON(dialog->priv->cd_radius_spin), radius);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(dialog->priv->cd_hole_spin), hole);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(dialog->priv->cd_w_spin), w);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(dialog->priv->cd_h_spin), h);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(dialog->priv->cd_waste_spin), waste);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON(dialog->priv->cd_margin_spin), margin);

}
