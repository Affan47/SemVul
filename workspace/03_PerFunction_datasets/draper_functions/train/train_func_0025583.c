pars_create_all_awars(AW_root *awr, AW_default aw_def)
{
    awr->awar_string(AWAR_SPECIES_NAME, "",     GLOBAL_gb_main);
    awr->awar_string(AWAR_FOOTER,       "",     aw_def);
    awr->awar_string(AWAR_FILTER_NAME,  "none", GLOBAL_gb_main);

    {
        GB_transaction  ta(GLOBAL_gb_main);
        char           *dali = GBT_get_default_alignment(GLOBAL_gb_main);

        awr->awar_string( AWAR_ALIGNMENT,dali ,GLOBAL_gb_main )->write_string(dali);
        free(dali);
    }

    awt_set_awar_to_valid_filter_good_for_tree_methods(GLOBAL_gb_main,awr,AWAR_FILTER_NAME);

    awr->awar_string(AWAR_FILTER_FILTER,"" ,GLOBAL_gb_main);
    awr->awar_string(AWAR_FILTER_ALIGNMENT,"" ,aw_def)     ;
    awr->awar       (AWAR_FILTER_ALIGNMENT)                ->map(AWAR_ALIGNMENT);

    awr->awar_string( "tmp/pars/csp/alignment",0 ,aw_def );
    awr->awar("tmp/pars/csp/alignment")->map(AWAR_ALIGNMENT);

    awr->awar_int( AWAR_PARS_TYPE,PARS_WAGNER ,GLOBAL_gb_main );

    {
        GB_transaction  ta(GLOBAL_gb_main);
        GBDATA *gb_tree_name = GB_search(GLOBAL_gb_main,AWAR_TREE,GB_STRING);
        char   *tree_name    = GB_read_string(gb_tree_name);

        awr->awar_string( AWAR_TREE,0 ,aw_def )->write_string(tree_name);
        free(tree_name);
    }

    awr->awar_int(AWAR_PARSIMONY,      0, aw_def);
    awr->awar_int(AWAR_BEST_PARSIMONY, 0, aw_def);
    awr->awar_int(AWAR_STACKPOINTER,   0, aw_def);

    create_parsimony_variables(awr, GLOBAL_gb_main);
    create_nds_vars(awr,aw_def,GLOBAL_gb_main);

#if defined(DEBUG)
    AWT_create_db_browser_awars(awr, aw_def);
#endif

    GB_ERROR error = ARB_init_global_awars(awr, aw_def, GLOBAL_gb_main);
    if (error) aw_message(error);
}
