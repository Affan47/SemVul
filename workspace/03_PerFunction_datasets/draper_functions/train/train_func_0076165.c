on_hscale1_value_changed               (GtkRange        *range,
                                        gpointer         user_data)
{
	gdouble val = gtk_range_get_value (range);
	gdouble sec = val*(stg[mem].end-stg[mem].start)/1000.0 + stg[mem].start;
	if (mode == 0 ) { return;}
	status_printf("jack reposition: %.3f sec", sec);
	jack_reposition(sec);
	if (mode == 2 ) {mode=0;}
}
