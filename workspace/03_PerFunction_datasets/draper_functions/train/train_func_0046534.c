create_genelike_entry(const char *internal_name, GBDATA *gb_species_data2, int start_pos, int end_pos, const char *ali_genome, const char *long_name) {
    GBDATA *gb_genespecies = create_gene_species(gb_species_data2, internal_name, long_name, start_pos, ali_genome+start_pos, end_pos-start_pos+1);
    return gb_genespecies ? 0 : GB_await_error();
}
