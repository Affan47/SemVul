count_key_data_elements(GBDATA *gb_key_data) {
    int nitems  = 0;
    for (GBDATA *gb_cnt = GB_child(gb_key_data); gb_cnt; gb_cnt = GB_nextChild(gb_cnt)) {
        ++nitems;
    }

    return nitems;
}
