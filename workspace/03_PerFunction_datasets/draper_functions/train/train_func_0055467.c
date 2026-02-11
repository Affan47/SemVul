deleteColorTranslationTable(AW_window *aws) {
    bool delete_table = aw_ask_sure("Are you sure you want to delete the selected COLOR TRANSLATION TABLE?");
    if (delete_table) {
        AW_root *aw_root = aws->get_root();
        char *clrTabName = aw_root->awar_string(AWAR_SAI_CLR_TRANS_TABLE)->read_string();

        if (clrTabName[0]) {
            AW_awar       *awar_tabNames    = aw_root->awar(AWAR_SAI_CLR_TRANS_TAB_NAMES);
            char          *clrTransTabNames = awar_tabNames->read_string();
            GBS_strstruct *newTransTabName  = GBS_stropen(strlen(clrTransTabNames));

            for (const char *tok = strtok(clrTransTabNames,"\n"); tok; tok = strtok(0,"\n")) {
                if (strcmp(clrTabName, tok) != 0) {
                    GBS_strcat(newTransTabName, tok);
                    GBS_strcat(newTransTabName, "\n");
                }
            }

            aw_root->awar_string(getClrDefAwar(clrTabName))->write_string("");
            char *new_name = GBS_strclose(newTransTabName);
            awar_tabNames->write_string(new_name);
            free(new_name);

            free(clrTransTabNames);
        }
        else {
            aw_message("Selected Color Translation Table is not VALID and cannot be DELETED!");
        }
        free(clrTabName);
    }
}
