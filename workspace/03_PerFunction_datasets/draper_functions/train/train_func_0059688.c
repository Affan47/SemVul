assign_SAI_to_group(AW_window *aww) {
    AW_root  *awr      = aww->get_root();
    char     *sai_name = awr->awar(AWAR_SAI_NAME)->read_string();
    GB_ERROR  error    = 0;

    if (!sai_name || !sai_name[0]) error = "No SAI selected";
    else {
        GBDATA *gb_sai;
        {
            GB_transaction ta(GLOBAL_gb_main);
            gb_sai = GBT_find_SAI(GLOBAL_gb_main, sai_name);
        }

        if (!gb_sai) error = GBS_global_string("SAI '%s' not found", sai_name);
        else {
            bool        has_group = true;
            const char *group     = GBT_read_char_pntr(gb_sai, "sai_group");
            if (!group) {
                group     = "default_group";
                has_group = false;
            }

            char *new_group;
            {
                char *existingGroups = getExistingSAIgroups();
                if (existingGroups) {
                    new_group = aw_string_selection("Assign SAI to group", "Enter group name:", group, existingGroups, NULL, NULL);
                    free(existingGroups);
                }
                else {
                    new_group = aw_input("Assign SAI to group", "Enter group name:", group);
                }
            }

            if (new_group) {
                GB_transaction t2(GLOBAL_gb_main);
                if (new_group[0]) error = GBT_write_string(gb_sai, "sai_group", new_group);
                else if (has_group) {
                    GBDATA *gb_group = GB_entry(gb_sai, "sai_group");
                    if (gb_group) error = GB_delete(gb_group);
                }
            }
        }
    }

    if (error) aw_message(error);
    free(sai_name);
}
