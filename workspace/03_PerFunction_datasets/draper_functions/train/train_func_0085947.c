set_image_interpolation_cb ( GtkWidget *widget, AnypaperWindow *window )
{
	int i, positionx, positiony;
	block_callback(window);
	i = gtk_combo_box_get_active (GTK_COMBO_BOX (window->priv->combo_interpolation));
	if (i == 0) window->parameters->interpolation=GDK_INTERP_NEAREST;
	if (i == 1) window->parameters->interpolation=GDK_INTERP_TILES;
	if (i == 2) window->parameters->interpolation=GDK_INTERP_BILINEAR;
	if (i == 3) window->parameters->interpolation=GDK_INTERP_HYPER;
	positionx = window->parameters->positionx;
	positiony = window->parameters->positiony;
	anypaper_image_make (window->image, window->parameters);
	window->parameters->positionx = positionx;
	window->parameters->positiony = positiony;
	anypaper_image_move (window->image, window->parameters);
	gtk_image_set_from_pixbuf(GTK_IMAGE(window->priv->preview), window->image->preview);
	unblock_callback(window);
}
