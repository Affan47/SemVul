jk_map_handle_duplicates(jk_map_t *m, const char *prp, char **v,
                                    int treatment, jk_logger_t *l)
{
    const char *oldv = jk_map_get_string(m, prp, NULL);
    if (oldv) {
        if ((treatment == JK_MAP_HANDLE_DUPLICATES)
            && jk_is_unique_property(prp) == JK_FALSE) {
            char *tmpv = jk_pool_alloc(&m->p,
                                       strlen(*v) + strlen(oldv) + 3);
            if (tmpv) {
                char sep = '*';
                if (jk_is_path_property(prp))
                    sep = PATH_SEPERATOR;
                else if (jk_is_cmd_line_property(prp))
                    sep = ' ';
                else if (jk_is_list_property(prp))
                    sep = ',';
                sprintf(tmpv, "%s%c%s", oldv, sep, *v);
            }
            *v = tmpv;
            if (JK_IS_DEBUG_LEVEL(l))
                jk_log(l, JK_LOG_DEBUG,
                       "Concatenated value is: %s -> %s",
                       prp, *v);
            return JK_FALSE;
        }
        else {
            jk_log(l, JK_LOG_WARNING,
                   "Duplicate key '%s' detected - previous value '%s'"
                   " will be overwritten with '%s'.",
                   prp, oldv ? oldv : "(null)", v ? *v : "(null)");
            return JK_TRUE;
        }
    }
    else {
        return JK_TRUE;
    }
}
