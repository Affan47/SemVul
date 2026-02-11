AWT_print_tree_to_file(AW_window *aww, AWT_canvas * ntw) {

    GB_transaction ta(ntw->gb_main);

    AW_root  *awr   = aww->get_root();
    char     *dest  = awt_get_selected_fullname(awr, AWAR_PRINT_TREE_FILE_BASE);
    GB_ERROR  error = 0;

    if (dest[0] == 0) {
        error = "Please enter a file name";
    }
    else {
        long what      = awr->awar(AWAR_PRINT_TREE_CLIP)->read_int();
        long handles   = awr->awar(AWAR_PRINT_TREE_HANDLES)->read_int();
        int  use_color = awr->awar(AWAR_PRINT_TREE_COLOR)->read_int();

        AW_device *device      = ntw->aww->get_print_device(AW_MIDDLE_AREA);
        AW_device *size_device = ntw->aww->get_size_device(AW_MIDDLE_AREA);

        device->reset();
        device->set_color_mode(use_color==1);
        error = device->open(dest);
        device->line(0, 0, 0, 1, -1);

        if (what) {
            AW_world size;
            size_device->reset();
            size_device->zoom(ntw->trans_to_fit);
            size_device->set_filter(AW_SCREEN);
            ntw->tree_disp->show(size_device);
            size_device->get_size_information(&size);
            size.l -= 50;
            size.t -= 40;
            size.r += 20;
            size.b += 20;
            device->set_offset(AW::Vector(size.l, size.t) / -ntw->trans_to_fit);
            device->set_bottom_clip_border((int)(size.b-size.t), true);
            device->set_right_clip_border((int)(size.r-size.l), true);
            device->zoom(ntw->trans_to_fit);
        }
        else {
            ntw->init_device(device);
        }

        if (!error) {
            if (handles) {
                device->set_filter(AW_PRINTER | AW_PRINTER_EXT);
            }
            else {
                device->set_filter(AW_PRINTER);
            }
            ntw->tree_disp->show(device);
            device->close();
            awr->awar(AWAR_PRINT_TREE_FILE_DIR)->touch();
        }
    }

    if (error) aw_message(error);

    free(dest);

    return error;
}
