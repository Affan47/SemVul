gui_handle_event( SDL_Event *sdl_event )
{
    GuiWidget *widget = 0;
    GuiEvent gui_event;

    switch ( sdl_event->type ) {
        case SDL_QUIT:
            stk_quit_request = 1;
            return 1;
        case SDL_KEYUP:
        case SDL_KEYDOWN:


            if ( gui_key_widget )
                widget = gui_key_widget;
            else
                widget = gui_focused_widget;
            if ( widget ) {
                gui_event_init( &gui_event, sdl_event );
                gui_widget_handle_event( widget, &gui_event );
                return 1;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:

            if ( !gui_focused_widget ) break;
            gui_clicked_widget = gui_focused_widget;
            widget = gui_focused_widget;
            widget->pressed = 1;
            if ( widget->grab_keys ) {
                if ( gui_key_widget )
                    gui_key_widget->default_event_handler(
                        gui_key_widget,
                        gui_event_get_simple( GUI_FOCUS_OUT ) );
                gui_key_widget = widget;
            }
            gui_event_init( &gui_event, sdl_event );
            gui_widget_handle_event( widget, &gui_event );
            return 1;
        case SDL_MOUSEBUTTONUP:


            if ( gui_clicked_widget )
            if ( gui_clicked_widget->pressed )
            if ( gui_clicked_widget->grab_focus ) {
                memset( &gui_event, 0, sizeof( gui_event ) );
                gui_event.type = GUI_MOTION;
                gui_event.motion.x = sdl_event->button.x;
                gui_event.motion.y = sdl_event->button.y;


                gui_update_focus( &gui_event );
            }


            if ( !gui_focused_widget ) {
                if ( gui_clicked_widget )
                    gui_clicked_widget->pressed = 0;
                break;
            }
            gui_event_init( &gui_event, sdl_event );
            widget = gui_focused_widget;
            if ( widget->pressed )
                gui_event.type = GUI_CLICKED;
            else
                gui_event.type = GUI_BUTTON_RELEASED;
            if ( gui_clicked_widget )
                gui_clicked_widget->pressed = 0;
            gui_widget_handle_event( widget, &gui_event );
            return 1;
        case SDL_MOUSEMOTION:


            if ( gui_uses_event_filter ) {
                gui_event_init( &gui_event, &gui_sdl_motion_event );
                gui_sdl_motion_event.type = SDL_NOEVENT;
            }
            else
                gui_event_init( &gui_event, sdl_event );


            if ( gui_clicked_widget )
            if ( gui_clicked_widget->pressed )
            if ( gui_clicked_widget->grab_focus ) {
                gui_widget_handle_event( gui_clicked_widget, &gui_event );
                break;
            }


            gui_update_focus( &gui_event );
            break;
    }
    return 0;
}
