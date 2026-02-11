orte_rmaps_rank_file_parse_string_or_int(void)
{
    int rc;
    char tmp_str[64];

    if (ORTE_RANKFILE_EQUAL != orte_rmaps_rank_file_lex()){
        return NULL;
    }

    rc = orte_rmaps_rank_file_lex();
    switch (rc) {
        case ORTE_RANKFILE_STRING:
            return strdup(orte_rmaps_rank_file_value.sval);
        case ORTE_RANKFILE_INT:
            sprintf(tmp_str,"%d",orte_rmaps_rank_file_value.ival);
            return strdup(tmp_str);
        default:
            return NULL;

    }

}
