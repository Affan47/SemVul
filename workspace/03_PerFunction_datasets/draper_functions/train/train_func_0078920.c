nt_build_sai_string(GBS_strstruct *topfile, GBS_strstruct *middlefile){
    GBDATA *gb_sai_data = GBT_get_SAI_data(GLOBAL_gb_main);
    if (!gb_sai_data) return;

    GB_HASH *hash = GBS_create_hash(100, GB_IGNORE_CASE);
    GBDATA  *gb_sai;

    for (gb_sai = GBT_first_SAI_rel_SAI_data(gb_sai_data); gb_sai; gb_sai = GBT_next_SAI(gb_sai)) {
        GBDATA *gb_name = GB_search(gb_sai,"name",GB_FIND);
        if (!gb_name) continue;

        char *name = GB_read_string(gb_name);

        if (strcmp(name,  "HELIX") == 0  || strcmp(name,  "HELIX_NR") == 0 || strcmp(name,  "ECOLI") == 0) {
            GBS_chrcat(topfile,1);
            GBS_strcat(topfile,"S");
            GBS_strcat(topfile,name);
        }
        else {
            GBDATA *gb_gn = GB_search(gb_sai,"sai_group",GB_FIND);
            char   *gn;

            if (gb_gn)  gn = GB_read_string(gb_gn);
            else        gn = strdup("SAI's");

            char *cn = new char[strlen(gn) + strlen(name) + 2];
            sprintf(cn,"%s%c%s",gn,1,name);
            GBS_write_hash(hash,cn,1);
            free(name);
            delete [] cn;
            free(gn);
        }
    }


    GBS_chrcat(middlefile, 1);
    GBS_strcat(middlefile, "GSAI-Maingroup");

    struct SAI_string_builder sai_builder = { middlefile, 0};
    GBS_hash_do_sorted_loop(hash, nt_build_sai_string_by_hash, GBS_HCF_sortedByKey, &sai_builder);
    if (sai_builder.last_group_name) {
        GBS_chrcat(middlefile,1);
        GBS_chrcat(middlefile,'E');
    }


    GBS_chrcat(middlefile,1);
    GBS_chrcat(middlefile,'E');

    GBS_free_hash(hash);
}
