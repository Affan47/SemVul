CPRO_savestatistic_cb(AW_window *aw,AW_CL which_statistic)
{
    AW_root  *awr      = aw->get_root();
    char     *filename = awr->awar("cpro/save/file_name")->read_string();
    GB_ERROR  error    = 0;

    if (!filename) {
        error = "no filename";
    }
    else {
        const CPRO_result_struct& curr_stat = CPRO.result[which_statistic];
        if (!(curr_stat.statisticexists)) {
            error = "calculate first!";
        }
        else {
            GBDATA *newbase     = GB_open(filename,"wc");
            if (!newbase) error = GB_await_error();
            else {
                error = GB_begin_transaction(newbase);

                if (!error) error = GBT_write_int   (newbase, "cpro_resolution",    curr_stat.resolution);
                if (!error) error = GBT_write_int   (newbase, "cpro_maxalignlen",   curr_stat.maxalignlen);
                if (!error) error = GBT_write_int   (newbase, "cpro_maxaccu",       curr_stat.maxaccu);
                if (!error) error = GBT_write_int   (newbase, "cpro_memneeded",     curr_stat.memneeded);
                if (!error) error = GBT_write_string(newbase, "cpro_alignname",     curr_stat.alignname);
                if (!error) error = GBT_write_string(newbase, "cpro_which_species", curr_stat.which_species);
                if (!error) error = GBT_write_float (newbase, "cpro_ratio",         curr_stat.ratio);
                if (!error) error = GBT_write_int   (newbase, "cpro_gaps",          curr_stat.countgaps);

                if (!error) {
                    long maxalignlen = curr_stat.maxalignlen;

                    for (long column = 0; column<curr_stat.resolution && !error; column++) {
                        GBDATA   *gb_colrescontainer = GB_create_container(newbase,"column");
                        GBDATA   *gb_colentry;
                        GB_UINT4 *pointer;

                        if (!error && (pointer = curr_stat.statistic[column*3+0])) {
                            gb_colentry = GB_create(gb_colrescontainer, "equal", GB_INTS);
                            error       = GB_write_ints(gb_colentry, pointer, maxalignlen);
                        }
                        if (!error && (pointer = curr_stat.statistic[column*3+1])) {
                            gb_colentry = GB_create(gb_colrescontainer, "group", GB_INTS);
                            error       = GB_write_ints(gb_colentry, pointer, maxalignlen);
                        }
                        if (!error && (pointer = curr_stat.statistic[column*3+2])) {
                            gb_colentry = GB_create(gb_colrescontainer, "different", GB_INTS);
                            error       = GB_write_ints(gb_colentry, pointer, maxalignlen);
                        }
                    }
                }
                error = GB_end_transaction(newbase, error);
                if (!error) error = GB_save(newbase,(char*)0,"b");
            }

            GB_close(newbase);
        }
    }

    free(filename);
    aw->hide_or_notify(error);
}
