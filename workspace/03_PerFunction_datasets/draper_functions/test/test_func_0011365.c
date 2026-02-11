has_species_name(ED4_base *base, AW_CL cl_species_name)
{
    ED4_species_name_terminal *name_term = base->to_species_name_terminal();
    GBDATA *gbd = name_term->get_species_pointer();

    if (gbd) {
        const char *name = GB_read_char_pntr(gbd);
        e4_assert(name);
        int has_name = strcmp(name,(const char*)cl_species_name)==0;
        return has_name;
    }

    return 0;
}
