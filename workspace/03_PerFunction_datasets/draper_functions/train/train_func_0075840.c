netinfo_get_count (Netinfo * netinfo)
{

	g_return_val_if_fail (netinfo != NULL, 1);

	if (gtk_toggle_button_get_active
	    (GTK_TOGGLE_BUTTON (netinfo->limited))) {

		return (gushort)
		    gtk_spin_button_get_value (GTK_SPIN_BUTTON
					       (netinfo->count));

	} else {
		return -1;
	}
}
