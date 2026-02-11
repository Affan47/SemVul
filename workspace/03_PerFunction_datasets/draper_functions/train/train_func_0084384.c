create_new_sequence(AW_window *aww,AED_window *aedw, int do_what)
{
    AED_area_entry *help_area_entry;
    AD_SPECIES sp;
    GB_ERROR error = 0;
    aedw->root->ad_main->begin_transaction();
    char *spname = aww->get_root()->awar(AWAR_SPECIES_DEST)->read_string();

    do {
        switch (do_what){
            case 2:
                if (!aedw->selected_area_entry) {
                    error = "Error: Please select a sequence first";
                }else{
                    const char *source = aedw->selected_area_entry->ad_species->name();
                    error = species_copy_cb(source,spname);
                }
                break;
            default:
                if (does_species_exists(spname)) {
                    if (do_what == 1) error = GB_export_errorf("Species %s already exists",spname);
                }else{
                    if (do_what == 0) error = GB_export_errorf("Cannot find species %s",spname);
                }
        }
        if (error) break;

        sp.init(aedw->root->ad_main);
        AD_ERR *ad_err = sp.create(spname);
        if (!ad_err) {
            help_area_entry = new AED_area_entry;
            help_area_entry->ad_species = new AD_SPECIES;
            help_area_entry->ad_extended = 0;
            *(help_area_entry->ad_species) = sp;
            help_area_entry->ad_container = new AD_CONT;
            if (do_what != 1) {
                help_area_entry->ad_container->init(help_area_entry->ad_species,
                                                    (AD_ALI *)aedw->alignment);
            }else{
                help_area_entry->ad_container->create(help_area_entry->ad_species,
                                                      (AD_ALI *)aedw->alignment);
            }
            if (!help_area_entry->ad_container->eof()) {
                help_area_entry->ad_stat = new AD_STAT ;
                help_area_entry->adt_sequence = new ADT_SEQUENCE;
                help_area_entry->ad_stat->init(help_area_entry->ad_container);
                help_area_entry->adt_sequence->init((ADT_ALI *)aedw->alignment,help_area_entry->ad_container);
            }else{
                help_area_entry->ad_stat = 0;
                help_area_entry->adt_sequence = 0;
            }
            help_area_entry->in_area = aedw->area_top;
            aedw->area_top->append(help_area_entry);
        }else{
            aw_message(ad_err->show());
            delete ad_err;
        }
        sp.exit();
    } while (0);
    if (error){
        aedw->root->ad_main->abort_transaction();
        aw_message(error);
    }else{
        aedw->root->ad_main->commit_transaction();
        aww->get_root()->awar(AWAR_SPECIES_DEST)->write_string("");
        aww->hide();
    }

    aedw->calculate_size(aedw->aww);
}
