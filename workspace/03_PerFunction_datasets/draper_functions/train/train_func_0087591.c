gpolljack (gpointer data) {
	GtkWidget *scale = lookup_widget(window1,"hscale1");
	double val=500;
	double jt=jack_poll_time();
	update_playpause_btn();

	if (jt < 0 ) { dothejack(0); return (TRUE);}
	update_smpte(jt);

	val = (jt-stg[mem].start)/(stg[mem].end-stg[mem].start)*1000.0;

	if (mode != 0 ) { return (TRUE);}
	gtk_range_set_value (GTK_RANGE(scale),val);
	return(TRUE);
}
