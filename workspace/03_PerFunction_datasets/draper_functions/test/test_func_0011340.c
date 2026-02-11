awt_get_selected_species(GBDATA *gb_main, AW_root *aw_root) {
    char   *species_name = aw_root->awar(AWAR_SPECIES_NAME)->read_string();
    GBDATA *gb_species   = 0;
    if (species_name[0]) {
        gb_species = GBT_find_species(gb_main, species_name);
    }
    free(species_name);
    return gb_species;
}
