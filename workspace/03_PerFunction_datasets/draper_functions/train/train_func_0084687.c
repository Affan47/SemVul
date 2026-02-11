drag_box(AW_device *device, int gc, AW_pos x, AW_pos y, AW_pos width, AW_pos height, char *str) {
    if( width == 0 ) {
        const AW_font_information *font_information = device->get_font_information( AED_GC_SELECTED_DRAG, 'A' );

        width  = strlen( str ) * font_information->max_letter.width + 4;
        height = font_information->max_letter.height + 4;
    }
    AW_pos y_help = y + 2;
    device->box(gc, false, x, y_help-height, width, height, AED_F_ALL, (AW_CL)"drag_box", 0);
    device->text( gc, str, x+2, y-2, 0, AED_F_ALL, (AW_CL)"drag_box", 0 );
}
