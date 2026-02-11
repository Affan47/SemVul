set_current(int idx) {
    GBDATA   *gb_num = GB_search(gb_structures, "current", GB_INT);
    GB_ERROR  error;

    if (!gb_num) error = GB_await_error();
    else {
        sec_assert(find(idx));
        error = GB_write_int(gb_num, idx);
    }
    return error;
}
