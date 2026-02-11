ratio_combobox_changed_cb (GtkComboBox     *combobox,
			   GthFileToolCrop *self)
{
	GtkWidget *ratio_w_spinbutton;
	GtkWidget *ratio_h_spinbutton;
	int        idx;
	int        w, h;
	gboolean   use_ratio;
	double     ratio;

	ratio_w_spinbutton = GET_WIDGET ("ratio_w_spinbutton");
	ratio_h_spinbutton = GET_WIDGET ("ratio_h_spinbutton");
	w = h = 1;
	use_ratio = TRUE;
	idx = gtk_combo_box_get_active (GTK_COMBO_BOX (self->priv->ratio_combobox));

	switch (idx) {
	case GTH_ASPECT_RATIO_NONE:
		use_ratio = FALSE;
		break;
	case GTH_ASPECT_RATIO_SQUARE:
		w = h = 1;
		break;
	case GTH_ASPECT_RATIO_IMAGE:
		w = self->priv->pixbuf_width;
		h = self->priv->pixbuf_height;
		break;
	case GTH_ASPECT_RATIO_DISPLAY:
		w = self->priv->screen_width;
		h = self->priv->screen_height;
		break;
	case GTH_ASPECT_RATIO_5x4:
		w = 5;
		h = 4;
		break;
	case GTH_ASPECT_RATIO_4x3:
		w = 4;
		h = 3;
		break;
	case GTH_ASPECT_RATIO_7x5:
		w = 7;
		h = 5;
		break;
	case GTH_ASPECT_RATIO_3x2:
		w = 3;
		h = 2;
		break;
	case GTH_ASPECT_RATIO_16x10:
		w = 16;
		h = 10;
		break;
	case GTH_ASPECT_RATIO_16x9:
		w = 16;
		h = 9;
		break;
	case GTH_ASPECT_RATIO_185x100:
		w = 185;
		h = 100;
		break;
	case GTH_ASPECT_RATIO_239x100:
		w = 239;
		h = 100;
		break;
	case GTH_ASPECT_RATIO_CUSTOM:
	default:
		w = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (ratio_w_spinbutton));
		h = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (ratio_h_spinbutton));
		break;
	}

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (GET_WIDGET ("invert_ratio_checkbutton"))))
		ratio = (double) h / w;
	else
		ratio = (double) w / h;

	gtk_widget_set_sensitive (GET_WIDGET ("custom_ratio_box"), idx == GTH_ASPECT_RATIO_CUSTOM);
	gtk_widget_set_sensitive (GET_WIDGET ("invert_ratio_checkbutton"), use_ratio);
	set_spin_value (self, ratio_w_spinbutton, w);
	set_spin_value (self, ratio_h_spinbutton, h);
	gth_image_selector_set_ratio (GTH_IMAGE_SELECTOR (self->priv->selector),
				      use_ratio,
				      ratio,
				      FALSE);
}
