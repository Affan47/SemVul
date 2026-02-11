orte_sstore_base_metadata_read_next_seq_num(FILE *file)
{
    char *token = NULL;
    char *value = NULL;
    int seq_int = -1;

    do {
        if( ORTE_SUCCESS != orte_sstore_base_metadata_read_next_token(file, &token, &value) ) {
            seq_int = -1;
            goto cleanup;
        }
    } while(0 != strncmp(token, SSTORE_METADATA_INTERNAL_DONE_SEQ_STR, strlen(SSTORE_METADATA_INTERNAL_DONE_SEQ_STR)));

    seq_int = atoi(value);

 cleanup:
    if( NULL != token) {
        free(token);
        token = NULL;
    }

    if( NULL != value) {
        free(value);
        value = NULL;
    }

    return seq_int;
}
