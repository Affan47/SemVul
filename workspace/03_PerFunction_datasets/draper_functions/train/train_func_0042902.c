add_species_to_merge_list(void **SpeciesMergeListPtr, void **GBDATAPtr, ED4_base *base)
{
    if (base->is_species_name_terminal()) {
        ED4_species_name_terminal *name_term       = base->to_species_name_terminal();
        char                      *species_name    = name_term->resolve_pointer_to_string_copy();
        GBDATA                    *gb_species_data = (GBDATA*)GBDATAPtr;
        GBDATA                    *gb_species      = GBT_find_species_rel_species_data(gb_species_data, species_name);

        if (gb_species) {
            SpeciesMergeList *smlp = (SpeciesMergeList*)SpeciesMergeListPtr;
            SpeciesMergeList sml = new S_SpeciesMergeList;
            sml->species = gb_species;
            sml->species_name = strdup(species_name);
            sml->next = *smlp;
            *smlp = sml;
        }

        free(species_name);
    }
    return ED4_R_OK;
}
