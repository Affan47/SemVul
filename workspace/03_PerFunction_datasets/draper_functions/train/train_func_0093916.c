update_species_counters() {
    int m;
    int sp  = 0;
    int sel = 0;

    for (m=0; m<children->members(); m++) {
        ED4_base *member = children->member(m);

        if (member->is_group_manager()) {
            ED4_multi_species_manager *multi_species_man = member->to_manager()->get_defined_level(ED4_L_MULTI_SPECIES)->to_multi_species_manager();

            if (!multi_species_man->has_valid_counters()) {
                multi_species_man->update_species_counters();
            }
            sel += multi_species_man->get_no_of_selected_species();
            sp += multi_species_man->get_no_of_species();
        }
        else if (member->is_species_manager()) {
            ED4_species_manager *species_man = member->to_species_manager();

            if (!species_man->flag.is_consensus) {
                ED4_species_name_terminal *species_name = species_man->search_spec_child_rek(ED4_L_SPECIES_NAME)->to_species_name_terminal();

                sp++;
                if (species_name->flag.selected) {
                    sel++;
                }
            }
        }
    }
    set_species_counters(sp, sel);
}
