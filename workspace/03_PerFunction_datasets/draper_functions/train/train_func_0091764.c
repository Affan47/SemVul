event_cb( EgeAdjustmentAction* act, GdkEvent* evt )
{
    gboolean handled = FALSE;
    if ( evt->type == GDK_BUTTON_PRESS ) {
        if ( evt->button.button == 3 ) {
            if ( IS_EGE_ADJUSTMENT_ACTION(act) ) {
                GdkEventButton* btnevt = (GdkEventButton*)evt;
                GtkWidget* menu = create_popup_number_menu(act);
                gtk_widget_show_all( menu );
                gtk_menu_popup( GTK_MENU(menu), NULL, NULL, NULL, NULL, btnevt->button, btnevt->time );
            }
            handled = TRUE;
        }
    }

    return handled;
}
