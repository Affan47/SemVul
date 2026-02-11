get_exposure(GtkWidget *window)
{
	GtkWidget *exposure;
	float value;
	int num, denom;
	const char *exp_text;

	exposure = gtk_object_get_data(GTK_OBJECT(window), "guide_exp_combo_entry");
	exp_text = gtk_entry_get_text (GTK_ENTRY (exposure));
	if(sscanf(exp_text, "%d/%d", &num, &denom) == 2) {
		return (float)num / denom;
	}
	if(sscanf(exp_text, "%f", &value) == 1) {
		return value;
	}
	return 1.0;
}
