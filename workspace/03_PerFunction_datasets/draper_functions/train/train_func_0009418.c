cddb_get_response_code(cddb_conn_t *c, char **msg)
{
    char *line, *space;
    int code, rv;

    cddb_log_debug("cddb_get_response_code()");
    line = cddb_read_line(c);
    if (!line) {
        if (cddb_errno(c) != CDDB_ERR_OK) {
            cddb_errno_log_error(c, CDDB_ERR_UNEXPECTED_EOF);
        }
        return -1;
    }

    rv = sscanf(line, "%d", &code);
    if (rv != 1) {
        cddb_errno_log_error(c, CDDB_ERR_INVALID_RESPONSE);
        return -1;
    }

    space = strchr(line, CHR_SPACE);
    if (space == NULL) {
        cddb_errno_log_error(c, CDDB_ERR_INVALID_RESPONSE);
        return -1;
    }
    *msg = space + 1;

    cddb_errno_set(c, CDDB_ERR_OK);
    cddb_log_debug("...code = %d (%s)", code, *msg);
    return code;
}
