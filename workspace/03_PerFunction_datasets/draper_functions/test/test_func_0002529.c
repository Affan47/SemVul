panel_applet_get_request_mode (GtkWidget *widget)
{
        PanelApplet *applet = PANEL_APPLET (widget);
        PanelAppletOrient orientation;

        orientation = panel_applet_get_orient (applet);
        if (orientation == PANEL_APPLET_ORIENT_UP ||
            orientation == PANEL_APPLET_ORIENT_DOWN)
                return GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH;

        return GTK_SIZE_REQUEST_WIDTH_FOR_HEIGHT;
}
