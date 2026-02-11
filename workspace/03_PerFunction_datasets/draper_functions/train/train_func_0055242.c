species_copy_cb(const char *source, char *dest){
    GB_ERROR error = 0;
    GBDATA *gb_species_data = GB_search(GLOBAL_gb_main,"species_data",GB_CREATE_CONTAINER);
    GBDATA *gb_species = GBT_find_species_rel_species_data(gb_species_data,source);
    GBDATA *gb_dest = GBT_find_species_rel_species_data(gb_species_data,dest);

    if (gb_dest) {
        error = "Sorry: species already exists";
    }else   if (gb_species) {
        gb_dest = GB_create_container(gb_species_data,"species");
        error = GB_copy(gb_dest,gb_species);
        if (!error) {
            GBDATA *gb_name =
                GB_search(gb_dest,"name",GB_STRING);
            error = GB_write_string(gb_name,dest);
        }
    }else{
        error = "Please select a species first";
    }

    return error;
}
