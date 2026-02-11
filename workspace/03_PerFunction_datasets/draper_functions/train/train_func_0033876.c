show_mode_callback (GtkWidget *widget, gpointer   data)
{
	long k,k2;
	k2 = (long) data;
	if(!((GtkCheckMenuItem*)(show_mode_buttons[k2]))->active) return 1;
	if(signal_menu_change>0) {signal_menu_change--;return 1;}


	k = (long) context->get_value("show_mode");
	if(k == k2) return 1;
	pthread_mutex_lock(&context_lock);
	context->set_value("show_mode","int",(void*)k2);
	pthread_mutex_unlock(&context_lock);


	return 0;
}
