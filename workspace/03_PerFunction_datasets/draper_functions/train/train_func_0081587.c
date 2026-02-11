copy() {
    ast_extra_info_string * s = new ast_extra_info_string(str);
    s->base_copy(this);
    return s;
}
