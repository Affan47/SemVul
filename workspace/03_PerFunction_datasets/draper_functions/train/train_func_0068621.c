init(GBDATA *gb_helix_nr, GBDATA *gb_helix, size_t sizei) {
    clear_error();

    if (!gb_helix) set_error("Can't find SAI:HELIX");
    else if (!gb_helix_nr) set_error("Can't find SAI:HELIX_NR");
    else {
        GB_transaction ta(gb_helix);
        initFromData(GB_read_char_pntr(gb_helix_nr), GB_read_char_pntr(gb_helix), sizei);
    }

    return get_error();
}
