copyTo(const char *structure_name) {
    GB_ERROR error = 0;
    GB_transaction ta(gb_structures);

    sec_assert(find(current()) == gb_current);

    error = store(gb_current);

    if (!error) {
        GBDATA *gb_new = create(structure_name);
        if (!gb_new) {
            sec_assert(st_error);
            error = st_error;
        }
        else {
            gb_current = gb_new;
        }
    }
    sec_assert(error || (find(current()) == gb_current));
    return ta.close(error);
}
