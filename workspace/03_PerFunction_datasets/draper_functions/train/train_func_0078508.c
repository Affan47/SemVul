orte_odls_base_open(mca_base_open_flag_t flags)
{
    char **ranks=NULL, *tmp;
    int rc, i, rank;
    orte_namelist_t *nm;
    bool xterm_hold;


    orte_local_children = OBJ_NEW(opal_pointer_array_t);
    if (OPAL_SUCCESS != (rc = opal_pointer_array_init(orte_local_children,
                                                      1,
                                                      ORTE_GLOBAL_ARRAY_MAX_SIZE,
                                                      1))) {
        ORTE_ERROR_LOG(rc);
        return rc;
    }


    OBJ_CONSTRUCT(&orte_odls_globals.xterm_ranks, opal_list_t);
    orte_odls_globals.xtermcmd = NULL;


    if (NULL != orte_xterm) {

        xterm_hold = false;
        orte_util_parse_range_options(orte_xterm, &ranks);
        for (i=0; i < opal_argv_count(ranks); i++) {
            if (0 == strcmp(ranks[i], "BANG")) {
                xterm_hold = true;
                continue;
            }
            nm = OBJ_NEW(orte_namelist_t);
            rank = strtol(ranks[i], NULL, 10);
            if (-1 == rank) {

                nm->name.vpid = ORTE_VPID_WILDCARD;
            } else if (rank < 0) {

                orte_show_help("help-odls-base.txt",
                               "orte-odls-base:xterm-neg-rank",
                               true, rank);
                return ORTE_ERROR;
            } else {


                nm->name.vpid = rank;
            }
            opal_list_append(&orte_odls_globals.xterm_ranks, &nm->super);
        }
        opal_argv_free(ranks);

        orte_odls_globals.xtermcmd = NULL;
        tmp = opal_find_absolute_path("xterm");
        if (NULL == tmp) {
            return ORTE_ERROR;
        }
        opal_argv_append_nosize(&orte_odls_globals.xtermcmd, tmp);
        free(tmp);
        opal_argv_append_nosize(&orte_odls_globals.xtermcmd, "-T");
        opal_argv_append_nosize(&orte_odls_globals.xtermcmd, "save");
        if (xterm_hold) {
            opal_argv_append_nosize(&orte_odls_globals.xtermcmd, "-hold");
        }
        opal_argv_append_nosize(&orte_odls_globals.xtermcmd, "-e");
    }


    return mca_base_framework_components_open(&orte_odls_base_framework, flags);
}
