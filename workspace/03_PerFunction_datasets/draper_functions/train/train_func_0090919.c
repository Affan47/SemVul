PV_DisplayAminoAcidNames(AW_root *root) {
    GB_transaction dummy(GLOBAL_gb_main);

    ED4_terminal *terminal = 0;
    for( terminal = ED4_ROOT->root_group_man->get_first_terminal();
         terminal;
         terminal = terminal->get_next_terminal())
        {
            if(terminal->is_sequence_terminal()) {
                ED4_sequence_terminal *seqTerminal = terminal->to_sequence_terminal();
                char                          *speciesName = seqTerminal->species_name;

                ED4_species_manager *speciesManager = terminal->get_parent(ED4_L_SPECIES)->to_species_manager();
                if (speciesManager && !speciesManager->flag.is_consensus && !speciesManager->flag.is_SAI)
                    {


                        for(int i=0; i<PV_AA_Terminals4Species; i++)
                            {

                                terminal = terminal->get_next_terminal()->get_next_terminal();

                                if (terminal->is_aa_sequence_terminal()) {
                                    ED4_AA_sequence_terminal *aaSeqTerminal = terminal->to_aa_sequence_terminal();

                                    int   aaStartPos = int(aaSeqTerminal->GET_aaStartPos());
                                    int aaStrandType = int(aaSeqTerminal->GET_aaStrandType());

                                    TranslateGeneToAminoAcidSequence(root, aaSeqTerminal, speciesName, aaStartPos-1, aaStrandType);
                                }
                            }
                    }
            }
        }

    PV_PrintMissingDBentryInformation();
    PV_RefreshWindow(root);
}
