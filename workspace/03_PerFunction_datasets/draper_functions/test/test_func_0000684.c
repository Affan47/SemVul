generate_message_fields_define(int gm_type, int count, gm_code_writer & Body) {
    for (int i = 0; i < count; i++) {
        const char* str = main->get_type_string(gm_type);
        const char* vname = get_message_field_var_name(gm_type, i);
        sprintf(str_buf, "%s %s;", str, vname);
        Body.pushln(str_buf);
        delete[] vname;
    }
}
