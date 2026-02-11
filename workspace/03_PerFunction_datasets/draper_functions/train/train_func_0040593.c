PV_AddCorrespondingAAseqTerminals(ED4_species_name_terminal *spNameTerm) {
    if(gTerminalsCreated) {
        if (spNameTerm && spNameTerm->is_species_name_terminal())
            {
                ED4_sequence_terminal *seqTerminal    = spNameTerm->corresponding_sequence_terminal()->to_sequence_terminal();
                ED4_species_manager *speciesManager = spNameTerm->get_parent(ED4_L_SPECIES)->to_species_manager();
                PV_AddNewAAseqTerminals(seqTerminal,speciesManager);
                PV_RefreshWindow(ED4_ROOT->aw_root);
            }
    }
}
