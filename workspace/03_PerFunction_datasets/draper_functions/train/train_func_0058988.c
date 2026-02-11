aed_config_window_motion(AW_window *aw, AW_CL cd1, AW_CL cd2) {
    AWUSE(cd2);
    AED_window                  *aedw = (AED_window *)cd1;
    AW_event                    event;
    AW_event                    motion_event;
    AW_device                   *device;
    AW_device                   *click_device;

    AW_clicked_text             clicked_text;
    AW_rectangle                screen;

    device = aw->get_device (AW_MIDDLE_AREA  );
    device->set_filter(AED_F_ALL);
    device->get_area_size( &screen );

    if ( aedw->drag ) {
        aw->get_event ( &motion_event );
        device->set_offset(AW::Vector());
        drag_box( device, 2, aedw->drag_x - aedw->drag_x_correcting, aedw->drag_y - aedw->drag_y_correcting, 0, 0, aedw->selected_entry_of_dlist_left_side->text_for_dragging );

        if( motion_event.y < 20 )
            motion_event.y = 20;
        if ( motion_event.y > screen.b )
            motion_event.y = screen.b;
        if( motion_event.x < 0 )
            motion_event.x = 0;
        if( motion_event.x > screen.r )
            motion_event.x = screen.r;
        aedw->drag_x = motion_event.x;
        aedw->drag_y = motion_event.y;

        drag_box( device, 2, motion_event.x - aedw->drag_x_correcting, motion_event.y - aedw->drag_y_correcting, 0, 0, aedw->selected_entry_of_dlist_left_side->text_for_dragging );
    }

    if( !aedw->drag ) {
        aw->get_event( &event );

        click_device = aw->get_click_device (AW_MIDDLE_AREA, event.x, event.y, 0, 0, 0 );
        click_device->set_filter(AED_F_TEXT_1);
        show_config_window_draw_area( click_device, aedw, aedw->config_window->slider_pos_horizontal, aedw->config_window->slider_pos_vertical,
                                      aedw->config_window->picture->l, aedw->config_window->top_indent_of_vertical_scrollbar );
        click_device->get_clicked_text( &clicked_text );

        if( clicked_text.exists && (AED_left_side *)clicked_text.client_data1 == aedw->selected_entry_of_dlist_left_side ) {
            aedw->drag = true;
            aw->get_event ( &motion_event );
            aedw->drag_x_correcting = event.x - aedw->selected_entry_of_dlist_left_side->absolut_x;
            aedw->drag_y_correcting = event.y - aedw->selected_entry_of_dlist_left_side->absolut_y;
            device->set_offset(AW::Vector());
            drag_box( device, 2, motion_event.x - aedw->drag_x_correcting, motion_event.y - aedw->drag_y_correcting, 0, 0, aedw->selected_entry_of_dlist_left_side->text_for_dragging );
            aedw->drag_x = motion_event.x;
            aedw->drag_y = motion_event.y;
        }
    }
}
