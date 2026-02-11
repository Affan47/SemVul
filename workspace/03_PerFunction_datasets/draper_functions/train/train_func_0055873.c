rdlist_read_field_num(rdlist_t* ls, int ext, rd_t* fld) {
    if (rdlist_open_field(ls, ext)) {
        return NULL;
    }
    return rdlist_read_field(ls, fld);
}
