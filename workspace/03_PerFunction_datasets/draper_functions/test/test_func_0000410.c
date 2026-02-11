gb_hig_vbox_new (gbHigVBoxType type)
{
	GtkWidget    *hig_vbox;

	hig_vbox = g_object_new (gb_hig_vbox_get_type (), NULL);

	switch (type) {

	case GB_HIG_VBOX_OUTER:
		gtk_box_set_spacing (GTK_BOX(hig_vbox),
				     HIG_VBOX_OUTER_SPACING);
		gtk_container_set_border_width (GTK_CONTAINER(hig_vbox),
						HIG_VBOX_OUTER_BORDER);
		break;

	case GB_HIG_VBOX_INNER:
		gtk_box_set_spacing (GTK_BOX(hig_vbox),
				     HIG_VBOX_INNER_SPACING);
		gtk_container_set_border_width (GTK_CONTAINER(hig_vbox), 0);

	default:
		break;

	}

	return hig_vbox;
}
