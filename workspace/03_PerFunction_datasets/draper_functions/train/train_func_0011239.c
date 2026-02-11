client_select_channel( GuiWidget *widget, GuiEvent *event )
{
    if ( event->type != GUI_CLICKED ) return;

    gui_list_update( list_channels, client_channels->count );
    if ( client_channels->count > 0 ) {
        gui_edit_set_text( edit_channel, list_first( client_channels ) );
        gui_list_select( list_channels, 0,0, 1 );
    }
    gui_widget_show( dlg_channels );
    client_state = CLIENT_SELECT_CHANNEL;
}
