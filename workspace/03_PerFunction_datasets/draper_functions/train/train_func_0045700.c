inv_display_fg_init(InvDisplayFG *displayFG)
{
	displayFG->bypass = INV_PLUGIN_ACTIVE;
	displayFG->mode = INV_DISPLAYFG_MODE_LPF;
	displayFG->freq = 1000.0;
	displayFG->gain = 0.0;
	displayFG->Lastfreq = 1000.0;
	displayFG->Lastgain = 0.0;
	displayFG->Laststate = GTK_STATE_NORMAL;

	displayFG->font_size=0;

    	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(displayFG), GTK_CAN_FOCUS);

	gtk_widget_set_tooltip_markup(GTK_WIDGET(displayFG),"<span size=\"8000\"><b>Description:</b> This shows the effect of the filter across the autio spectrum.\n<b>Usage:</b> Click on the dot and drag to adjust the filter.</span>");
}
