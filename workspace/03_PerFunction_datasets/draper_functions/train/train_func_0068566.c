get_next_selected_species(void)
{
    if (!actual_aligner_elem) return 0;

    ED4_selection_entry *selectionEntry = (ED4_selection_entry*)actual_aligner_elem->elem();
    ED4_species_manager *specMan = selectionEntry->object->get_parent(ED4_L_SPECIES)->to_species_manager();

    actual_aligner_elem = actual_aligner_elem->next();
    return specMan->get_species_pointer();
}
