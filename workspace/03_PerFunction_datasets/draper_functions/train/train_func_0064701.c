nt_check_database_consistency() {
    aw_openstatus("Checking database...");

    GB_ERROR err = NT_format_all_alignments(GLOBAL_gb_main);
    if (!err) err = NT_repair_DB(GLOBAL_gb_main);

    aw_closestatus();
    return err;
}
