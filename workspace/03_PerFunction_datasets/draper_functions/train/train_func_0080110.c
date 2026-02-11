SQ_pass1_no_tree(SQ_GroupData * globalData, GBDATA * gb_main,
        AP_filter * filter) {
    char *alignment_name;

    GBDATA *read_sequence = 0;
    GBDATA *gb_species;
    GBDATA *gb_species_data;
    GBDATA *gb_name;
    GBDATA *(*getFirst)(GBDATA *) = 0;
    GBDATA *(*getNext)(GBDATA *) = 0;
    GB_ERROR error = 0;

    GB_push_transaction(gb_main);
    gb_species_data = GB_search(gb_main, "species_data", GB_CREATE_CONTAINER);
    alignment_name = GBT_get_default_alignment(gb_main);seq_assert(alignment_name);

    getFirst = GBT_first_species;
    getNext = GBT_next_species;


    for (gb_species = getFirst(gb_main); gb_species && !error; gb_species
            = getNext(gb_species)) {

        gb_name = GB_entry(gb_species, "name");

        if (!gb_name)
            error = GB_get_error();
        else {
            GBDATA *gb_ali = GB_entry(gb_species, alignment_name);

            if (!gb_ali) {
                error = no_data_error(gb_species, alignment_name);
            } else {
                GBDATA *gb_quality = GB_search(gb_species, "quality",
                        GB_CREATE_CONTAINER);
                if (!gb_quality) {
                    error = GB_get_error();
                }

                read_sequence = GB_entry(gb_ali, "data");

                GBDATA *gb_quality_ali = GB_search(gb_quality, alignment_name,
                        GB_CREATE_CONTAINER);
                if (!gb_quality_ali)
                    error = GB_get_error();


                if (read_sequence) {
                    char *rawSequence = SQ_fetch_filtered_sequence(
                            read_sequence, filter);
                    int sequenceLength = filter->real_len;


                    SQ_physical_layout *ps_chan = new SQ_physical_layout();
                    ps_chan->SQ_calc_physical_layout(rawSequence,
                            sequenceLength, gb_quality_ali);


                    globalData->SQ_count_sequences();
                    globalData->SQ_set_avg_bases(ps_chan->
                    SQ_get_number_of_bases());
                    globalData->SQ_set_avg_gc(ps_chan->
                    SQ_get_gc_proportion());
                    delete ps_chan;


                    SQ_ambiguities *ambi_chan = new SQ_ambiguities();
                    ambi_chan->SQ_count_ambiguities(rawSequence,
                            sequenceLength, gb_quality_ali);
                    delete ambi_chan;


                    SQ_helix *heli_chan = new SQ_helix(sequenceLength);
                    heli_chan->SQ_calc_helix_layout(rawSequence, gb_main,
                            alignment_name, gb_quality_ali, filter);
                    delete heli_chan;


                    {
                        if (!globalData->SQ_is_initialized()) {
                            globalData->SQ_init_consensus(sequenceLength);
                        }
                        globalData->SQ_add_sequence(rawSequence);
                    }
                    pass1_counter_notree++;
                    aw_status((double) pass1_counter_notree
                            / (double) globalcounter_notree);

                    delete(rawSequence);
                }
            }
        }
    }

    free(alignment_name);

    if (error)
        GB_abort_transaction(gb_main);
    else
        GB_pop_transaction(gb_main);

    return error;
}
