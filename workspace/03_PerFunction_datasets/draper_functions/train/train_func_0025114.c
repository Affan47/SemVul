group_species_cb(AW_window *aww, AW_CL cl_use_fields, AW_CL) {

    int use_fields = int(cl_use_fields);

    if (!use_fields) {
        group_species(0, aww);
    }
    else {
        static AW_window *ask_field_window;

        if (!ask_field_window) ask_field_window = create_group_species_by_field_window(ED4_ROOT->aw_root, aww);
        ask_field_window->activate();
    }
}
