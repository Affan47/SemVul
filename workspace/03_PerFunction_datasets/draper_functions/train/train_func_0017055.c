applet_destroy_cb (PanelApplet *panel_applet, StickyNotesApplet *applet)
{
	GList *notes;

	stickynotes_save_now ();

	if (applet->destroy_all_dialog != NULL)
		gtk_widget_destroy (applet->destroy_all_dialog);

	if (applet->action_group)
		g_object_unref (applet->action_group);

	if (stickynotes->applets != NULL)
		stickynotes->applets = g_list_remove (stickynotes->applets, applet);

	if (stickynotes->applets == NULL) {
               notes = stickynotes->notes;
               while (notes) {
                       StickyNote *note = notes->data;
                       stickynote_free (note);
                       notes = g_list_next (notes);
               }
	}


}
