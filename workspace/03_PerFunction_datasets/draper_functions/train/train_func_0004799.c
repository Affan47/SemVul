create(const char *species_name) {
    GBDATA *species;
    if (strlen(species_name) < 2)
        return new AD_ERR("AD_SPECIES::too short name");
    species = GBT_find_or_create_species_rel_species_data(gb_spdata,species_name);
    gb_species = species;
    initpntr();
    return 0;
}
