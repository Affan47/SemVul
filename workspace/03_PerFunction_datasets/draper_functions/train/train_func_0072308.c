ap_getword_nulls(apr_pool_t *atrans, const char **line,
                                    char stop)
{
    const char *pos = ap_strchr_c(*line, stop);
    char *res;

    if (!pos) {
        apr_size_t len = strlen(*line);
        res = apr_pstrmemdup(atrans, *line, len);
        *line += len;
        return res;
    }

    res = apr_pstrndup(atrans, *line, pos - *line);

    ++pos;

    *line = pos;

    return res;
}
