parse_string_core(const char *cs, const size_t len, size_t pos,
                                stoken_t * st, char delim, size_t offset)
{


    const char *qpos =
        (const char *) memchr((const void *) (cs + pos + offset), delim,
                              len - pos - offset);


    if (offset > 0) {


        st->str_open = delim;
    } else {


        st->str_open = CHAR_NULL;
    }

    while (TRUE) {
        if (qpos == NULL) {


            st_assign(st, TYPE_STRING, pos + offset, len - pos - offset, cs + pos + offset);
            st->str_close = CHAR_NULL;
            return len;
        } else if ( is_backslash_escaped(qpos - 1, cs + pos + offset)) {

            qpos =
                (const char *) memchr((const void *) (qpos + 1), delim,
                                      (cs + len) - (qpos + 1));
            continue;
        } else if (is_double_delim_escaped(qpos, cs + len)) {

            qpos =
                (const char *) memchr((const void *) (qpos + 2), delim,
                                      (cs + len) - (qpos + 2));
            continue;
        } else {

            st_assign(st, TYPE_STRING, pos + offset,
                      qpos - (cs + pos + offset), cs + pos + offset);
            st->str_close = delim;
            return qpos - cs + 1;
        }
    }
}
