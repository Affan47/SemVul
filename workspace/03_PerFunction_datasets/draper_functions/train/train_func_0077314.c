addPlanesButtons(GtkWidget* box)
{
	GtkWidget *table;
	gint i;
	GtkWidget *separator;

  	table = gtk_table_new(3,3,FALSE);
	gtk_box_pack_start(GTK_BOX(box), table,TRUE,TRUE,0);

	i = 0;
	buttonYZPlanes = gtk_radio_button_new_with_label( NULL,"First direction" );
	gtk_table_attach(GTK_TABLE(table),buttonYZPlanes,0,3,i,i+1,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND) ,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),
		  3,3);

	i++;
	buttonXZPlanes = gtk_radio_button_new_with_label( gtk_radio_button_get_group (GTK_RADIO_BUTTON (buttonYZPlanes)), "Second direction");
	gtk_table_attach(GTK_TABLE(table),buttonXZPlanes,0,3,i,i+1,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND) ,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),
		  3,3);
	i++;
	buttonXYPlanes = gtk_radio_button_new_with_label( gtk_radio_button_get_group (GTK_RADIO_BUTTON (buttonYZPlanes)), "Third direction");
	gtk_table_attach(GTK_TABLE(table),buttonXYPlanes,0,3,i,i+1,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND) ,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),
		  3,3);
  	g_signal_connect (G_OBJECT(buttonXYPlanes), "toggled", G_CALLBACK (buttonPlanesSelected), NULL);
  	g_signal_connect (G_OBJECT(buttonXZPlanes), "toggled", G_CALLBACK (buttonPlanesSelected), NULL);
  	g_signal_connect (G_OBJECT(buttonYZPlanes), "toggled", G_CALLBACK (buttonPlanesSelected), NULL);
	switch(selectedPlanes)
	{
		case XYPLANES :
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (buttonXYPlanes), TRUE);
		break;
		case XZPLANES :
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (buttonXZPlanes), TRUE);
		break;
		case YZPLANES :
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (buttonYZPlanes), TRUE);
		break;
	}

	i++;
	separator = gtk_hseparator_new();
	gtk_table_attach(GTK_TABLE(table),separator,0,3,i,i+1,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND) ,
		  (GtkAttachOptions)(GTK_FILL | GTK_EXPAND),
		  3,3);
}
