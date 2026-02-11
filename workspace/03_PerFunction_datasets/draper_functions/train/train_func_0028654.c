MG_update_example(AW_root *aw_root) {
    char     *result       = 0;
    GB_ERROR  error        = 0;
    char     *curr_species = aw_root->awar(MG_left_AWAR_SPECIES_NAME())->read_string();

    if (!curr_species || !curr_species[0]) error = "No species selected.";
    else {
        GB_transaction  dummy(GLOBAL_gb_merge);
        GBDATA         *gb_species = GBT_find_species(GLOBAL_gb_merge, curr_species);

        if (!gb_species)                                    error = GB_export_errorf("No such species: '%s'", curr_species);
        else if (!GEN_is_pseudo_gene_species(gb_species))   error = "Selected species is no gene-species";
        else {
            result = MG_create_current_field_content(aw_root, gb_species, error);
        }
    }

    if (!error && !result) error = "no result";
    if (error) freeset(result, GBS_global_string_copy("<%s>", error));

    aw_root->awar(AWAR_MERGE_GENE_SPECIES_EXAMPLE)->write_string(result);

    free(result);
}
