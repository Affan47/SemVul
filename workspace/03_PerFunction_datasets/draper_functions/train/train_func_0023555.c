get_area_level(ED4_multi_species_manager **multi_species_manager) const
{

    ED4_base *temp_manager;
    temp_manager = get_parent( ED4_L_AREA );
    if (!temp_manager){
        return ED4_A_ERROR;
    }

    ED4_area_manager    *temp_parent;
    temp_parent = temp_manager->to_area_manager();

    if (temp_parent == ED4_ROOT->top_area_man)
    {
        if (multi_species_manager){
            *multi_species_manager = temp_parent->get_defined_level(ED4_L_MULTI_SPECIES)->to_multi_species_manager();
        }
        return ED4_A_TOP_AREA;
    }

    if (temp_parent == ED4_ROOT->middle_area_man)
    {
        if(multi_species_manager){
            *multi_species_manager = temp_parent->get_defined_level(ED4_L_MULTI_SPECIES)->to_multi_species_manager();
        }
        return ED4_A_MIDDLE_AREA;
    }

    return ED4_A_ERROR;
}
