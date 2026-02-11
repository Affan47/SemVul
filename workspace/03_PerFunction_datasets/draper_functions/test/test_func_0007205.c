main_window_accel_activate (GtkAccelGroup *accelgroup,
                                            GObject *arg1,
                                            guint value,
                                            GdkModifierType mod,
                                            gpointer user_data)
{
	MainWindow *mainwin = (MainWindow *)user_data;

	if (mainwin->summaryview &&
	    mainwin->summaryview->quicksearch &&
	    quicksearch_has_focus(mainwin->summaryview->quicksearch) &&
	    (mod == 0 || mod == GDK_SHIFT_MASK)) {
		quicksearch_pass_key(mainwin->summaryview->quicksearch, lastkey, mod);
		return TRUE;
	}
	return FALSE;
}
