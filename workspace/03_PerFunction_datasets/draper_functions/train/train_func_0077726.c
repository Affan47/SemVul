on_treeViewCrystals_key_press_event(GdkEventKey * event)
{
	LOG;

	switch (event->keyval)
	{
	case GDK_Insert:
	case GDK_KP_Insert:
		on_toolbutton_add_crystal_clicked();
		break;
	case GDK_Delete:
	case GDK_KP_Delete:
		on_toolbutton_del_crystal_clicked();
		break;
	}
	return true;
}
