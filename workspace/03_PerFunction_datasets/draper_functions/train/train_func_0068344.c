key_press_event ( GtkWidget *widget,
				  GdkEventKey *event ) {
	if (pressed)
		return TRUE;
	switch (event->keyval) {
	case GDK_1:
		selectedcolor = 0;
		tray_mid_click ();
		break;
	case GDK_2:
		selectedcolor = 1;
		tray_mid_click ();
		break;
	case GDK_3:
		selectedcolor = 2;
		tray_mid_click ();
		break;
	case GDK_4:
		selectedcolor = 3;
		tray_mid_click ();
		break;
	case GDK_5:
		selectedcolor = 4;
		tray_mid_click ();
		break;
	case GDK_6:
		selectedcolor = 5;
		tray_mid_click ();
		break;
	case GDK_7:
		selectedcolor = 6;
		tray_mid_click ();
		break;
	case GDK_8:
		selectedcolor = 7;
		tray_mid_click ();
		break;
	default:
		break;
	}

	return TRUE;
}
