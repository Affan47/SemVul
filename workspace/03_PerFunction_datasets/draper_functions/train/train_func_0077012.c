gui_dispatch_event( SDL_Event *sdl_event, int ms )
{
    ListEntry *entry;
    GuiEvent gui_event;
    GuiWidget *widget;
    int ret = 0;

    if ( ms > 0 ) {


        widget = gui_key_widget;
        if ( !widget ) widget = gui_focused_widget;
        if ( widget && widget->type == GUI_EDIT )
            gui_edit_update( widget, ms );

        gui_event.type = GUI_TIME_PASSED;
        gui_event.time.ms = ms;
        entry = gui_timed_stack->head->next;
        while ( entry != gui_timed_stack->tail ) {
            widget = (GuiWidget*)entry->item;
            if ( !widget->visible ) continue;
            gui_widget_call_user_event_handler(
                widget, &gui_event );
            entry = entry->next;
        }
    }

    if ( sdl_event )
        ret = gui_handle_event( sdl_event );
    return ret;
}
