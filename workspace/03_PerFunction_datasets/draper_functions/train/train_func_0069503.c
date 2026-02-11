Seeder_add_query(Seeder *seeder, Sequence *query){
    register Seeder_QueryInfo *query_info;
    g_assert(seeder);
    g_assert(query);
    g_assert(!seeder->is_prepared);
    if(seeder->verbosity > 2)
        g_message("Seeder Loading query [%s]", query->id);
    query_info = Seeder_QueryInfo_create(query);
    g_ptr_array_add(seeder->query_info_list, query_info);
    if(seeder->dna_loader)
        Seeder_load_query(seeder, query_info, seeder->dna_loader);
    if(seeder->protein_loader)
        Seeder_load_query(seeder, query_info, seeder->protein_loader);
    if(seeder->codon_loader)
        Seeder_load_query(seeder, query_info, seeder->codon_loader);

    return Seeder_memory_usage(seeder)
        >  (seeder->sas->fsm_memory_limit << 20);
    }
