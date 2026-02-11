NT_create_dna_2_pro_window(AW_root *root) {
    AWUSE(root);
    GB_transaction dummy(GLOBAL_gb_main);

    AW_window_simple *aws = new AW_window_simple;
    aws->init( root, "TRANSLATE_DNA_TO_PRO", "TRANSLATE DNA TO PRO");


    aws->load_xfig("transpro.fig");

    aws->callback( (AW_CB0)AW_POPDOWN);
    aws->at("close");
    aws->create_button("CLOSE","CLOSE","C");

    aws->callback( AW_POPUP_HELP,(AW_CL)"translate_dna_2_pro.hlp");
    aws->at("help");
    aws->create_button("HELP","HELP","H");

    aws->at("source");
    awt_create_selection_list_on_ad(GLOBAL_gb_main,(AW_window *)aws, AWAR_TRANSPRO_SOURCE,"dna=:rna=");

    aws->at("dest");
    awt_create_selection_list_on_ad(GLOBAL_gb_main,(AW_window *)aws, AWAR_TRANSPRO_DEST,"pro=:ami=");

    root->awar_int(AWAR_PROTEIN_TYPE, AWAR_PROTEIN_TYPE_bacterial_code_index, GLOBAL_gb_main);
    aws->at("table");
    aws->create_option_menu(AWAR_PROTEIN_TYPE);
    for (int code_nr=0; code_nr<AWT_CODON_TABLES; code_nr++) {
        aws->insert_option(AWT_get_codon_code_name(code_nr), "", code_nr);
    }
    aws->update_option_menu();

    aws->at("mode");
    aws->create_toggle_field(AWAR_TRANSPRO_MODE,0,"");
    aws->insert_toggle( "from fields 'codon_start' and 'transl_table'", "", "fields" );
    aws->insert_default_toggle( "use settings below (same for all species):", "", "settings" );
    aws->update_toggle_field();

    aws->at("pos");
    aws->create_option_menu(AWAR_TRANSPRO_POS,0,"");
    aws->insert_option( "1", "1", 0 );
    aws->insert_option( "2", "2", 1 );
    aws->insert_option( "3", "3", 2 );
    aws->update_option_menu();
    aws->get_root()->awar_int(AWAR_CURSOR_POSITION)->add_callback(nt_trans_cursorpos_changed);

    aws->at("write");
    aws->label("Save settings (to 'codon_start'+'transl_table')");
    aws->create_toggle(AWAR_TRANSPRO_WRITE);

    aws->at("start");
    aws->label("Translate all data");
    aws->create_toggle(AWAR_TRANSPRO_XSTART);

    aws->at("translate");
    aws->callback(transpro_event);
    aws->highlight();
    aws->create_button("TRANSLATE","TRANSLATE","T");

    aws->window_fit();

    return (AW_window *)aws;
}
