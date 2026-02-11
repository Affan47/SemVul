aed_motion( AW_window *aw, AW_CL cd1, AW_CL cd2 ) {
    AWUSE(cd2);
    AW_event event;
    AW_event motion_event;
    AW_device *device;
    AW_device *click_device;
    AED_window *aedw = (AED_window *)cd1;
    AW_window *awmm = aedw->aww;
    AW_clicked_text clicked_text;
    char left_text[100];

    device = aw->get_device (AW_MIDDLE_AREA  );
    device->set_filter(AED_F_ALL);

    if ( aedw->drag ) {
        aw->get_event ( &motion_event );
        device->set_offset(AW::Vector());
        aedw->make_left_text( left_text, aedw->selected_area_entry );
        drag_box( device, AED_GC_NAME_DRAG, aedw->drag_x - aedw->drag_x_correcting, aedw->drag_y - aedw->drag_y_correcting, 0, 0, left_text );
        aedw->drag_x = motion_event.x;
        aedw->drag_y = motion_event.y;
        drag_box( device, AED_GC_NAME_DRAG, motion_event.x - aedw->drag_x_correcting , motion_event.y - aedw->drag_y_correcting, 0, 0, left_text );
    }


    if( !aedw->drag && aedw->selected_area_entry) {
        aw->get_event( &event );
        click_device = aw->get_click_device (AW_MIDDLE_AREA, event.x, event.y, 10, 5, 0 );
        click_device->reset();
        click_device->set_filter(AED_F_NAME);
        aedw->show_data( click_device, awmm, false );
        click_device->get_clicked_text( &clicked_text );

        if( clicked_text.exists && clicked_text.client_data2 == AED_F_NAME ) {
            AED_area_entry *area_entry = (AED_area_entry *)clicked_text.client_data1;
            if( strcmp(area_entry->ad_species->name(),aedw->selected_area_entry->ad_species->name()) == 0 ) {
                aedw->drag = true;
                aw->get_event ( &motion_event );
                aedw->drag_x_correcting = event.x - (int)aedw->selected_area_entry->absolut_x;
                aedw->drag_y_correcting = event.y - (int)aedw->selected_area_entry->absolut_y;
                device->set_offset(AW::Vector());
                aedw->make_left_text( left_text, aedw->selected_area_entry );
                drag_box( device, AED_GC_NAME_DRAG, motion_event.x - aedw->drag_x_correcting , motion_event.y - aedw->drag_y_correcting, 0, 0, left_text );
                aedw->drag_x = motion_event.x;
                aedw->drag_y = motion_event.y;
            }
        }
    }

}
