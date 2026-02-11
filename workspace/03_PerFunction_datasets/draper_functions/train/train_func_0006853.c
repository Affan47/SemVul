on_goto_key_pressed (GtkWidget* entry, GdkEventKey* event, SearchBox* search_box)
{
	switch (event->keyval)
	{
		case GDK_KEY_0:
		case GDK_KEY_1:
		case GDK_KEY_2:
		case GDK_KEY_3:
		case GDK_KEY_4:
		case GDK_KEY_5:
		case GDK_KEY_6:
		case GDK_KEY_7:
		case GDK_KEY_8:
		case GDK_KEY_9:
		case GDK_KEY_KP_0:
		case GDK_KEY_KP_1:
		case GDK_KEY_KP_2:
		case GDK_KEY_KP_3:
		case GDK_KEY_KP_4:
		case GDK_KEY_KP_5:
		case GDK_KEY_KP_6:
		case GDK_KEY_KP_7:
		case GDK_KEY_KP_8:
		case GDK_KEY_KP_9:
		case GDK_KEY_Return:
		case GDK_KEY_KP_Enter:
		case GDK_KEY_BackSpace:
		case GDK_KEY_Delete:
		case GDK_KEY_Tab:
		{

			break;
		}
		case GDK_KEY_Escape:
		{
			search_box_hide (search_box);
		}
		default:
		{

			gdk_beep ();
			return TRUE;
		}
	}
	return FALSE;
}
