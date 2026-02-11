st_ml_add_quality_string_to_species(GBDATA * gb_main,
                                         const char *alignment_name, const char *species_name, int seq_len,
                                         int bucket_size, GB_HASH * species_to_info_hash, st_report_enum report,
                                         const char *dest_field)
{
    GBDATA *gb_species = GBT_find_species(gb_main, species_name);
    if (!gb_species) return;

    st_cq_info *info = (st_cq_info *) GBS_read_hash(species_to_info_hash, species_name);
    if (!info) return;

    GBDATA   *gb_dest   = GB_search(gb_species, dest_field, GB_STRING);
    GB_ERROR  error     = 0;
    if (!gb_dest) error = GB_await_error();
    else {
        char buffer[256];
        char *s2 = info->ss2.generate_string();
        char *s5 = info->ss5.generate_string();
        char *su = info->ssu.generate_string();
        snprintf(buffer, 256, "a%s b%s c%s", s2, s5, su);
        delete[]s2;
        delete[]s5;
        error = GB_write_string(gb_dest, buffer);

        if (!error && report) {
            GBDATA *gb_report = GBT_add_data(gb_species, alignment_name, "quality", GB_STRING);
            if (!gb_report) error = GB_await_error();
            else {
                char *rp = new char[seq_len + 1];
                rp[seq_len] = 0;
                int i;
                for (i = 0; i < seq_len; i++) {
                    rp[i] = su[i / bucket_size];
                }
                error = GB_write_string(gb_report, rp);
                if (report == ST_QUALITY_REPORT_TEMP) {
                    GB_set_temporary(gb_report);
                }
                delete rp;
            }
        }
        delete[]su;
    }
    if (error) {
        aw_message(error);
    }
    delete info;
    GBS_write_hash(species_to_info_hash, species_name, 0);

}
