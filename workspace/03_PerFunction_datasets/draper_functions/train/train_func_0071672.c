delete_old_sai(const char *sai_name) {
    GBDATA *gb_extended = GBT_find_SAI(gb_main, sai_name);
    if (gb_extended) {
        GBDATA *gb_ali = GB_search(gb_extended, ali_name, GB_FIND);
        if (gb_ali) {
            return GB_delete(gb_ali);
        }
    }
    return NULL;
}
