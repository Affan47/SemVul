size_allocate (PanelApplet  *applet,
	       GdkRectangle *allocation,
	       DriveList    *drive_list)
{
    int size;

    switch (panel_applet_get_orient (applet)) {
    case PANEL_APPLET_ORIENT_LEFT:
    case PANEL_APPLET_ORIENT_RIGHT:
	size = allocation->width;
	break;
    case PANEL_APPLET_ORIENT_UP:
    case PANEL_APPLET_ORIENT_DOWN:
    default:
	size = allocation->height;
	break;
    }
    drive_list_set_panel_size (drive_list, size);
}
