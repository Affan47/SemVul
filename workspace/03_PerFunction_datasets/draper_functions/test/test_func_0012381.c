join_append_data(WriterObj *self, unsigned int field_kind, void *field_data,
                 Py_ssize_t field_len, int quote_empty, int *quoted,
                 int copy_phase)
{
    DialectObj *dialect = self->dialect;
    int i;
    Py_ssize_t rec_len;

#define ADDCH(c) \
    do {\
        if (copy_phase) \
            self->rec[rec_len] = c;\
        rec_len++;\
    } while(0)

    rec_len = self->rec_len;


    if (self->num_fields > 0)
        ADDCH(dialect->delimiter);


    if (copy_phase && *quoted)
        ADDCH(dialect->quotechar);


    for (i = 0; field_data && (i < field_len); i++) {
        Py_UCS4 c = PyUnicode_READ(field_kind, field_data, i);
        int want_escape = 0;

        if (c == dialect->delimiter ||
            c == dialect->escapechar ||
            c == dialect->quotechar  ||
            PyUnicode_FindChar(
                dialect->lineterminator, c, 0,
                PyUnicode_GET_LENGTH(dialect->lineterminator), 1) >= 0) {
            if (dialect->quoting == QUOTE_NONE)
                want_escape = 1;
            else {
                if (c == dialect->quotechar) {
                    if (dialect->doublequote)
                        ADDCH(dialect->quotechar);
                    else
                        want_escape = 1;
                }
                if (!want_escape)
                    *quoted = 1;
            }
            if (want_escape) {
                if (!dialect->escapechar) {
                    PyErr_Format(error_obj,
                                 "need to escape, but no escapechar set");
                    return -1;
                }
                ADDCH(dialect->escapechar);
            }
        }


        ADDCH(c);
    }


    if (i == 0 && quote_empty) {
        if (dialect->quoting == QUOTE_NONE) {
            PyErr_Format(error_obj,
                "single empty field record must be quoted");
            return -1;
        }
        else
            *quoted = 1;
    }

    if (*quoted) {
        if (copy_phase)
            ADDCH(dialect->quotechar);
        else
            rec_len += 2;
    }
    return rec_len;
#undef ADDCH
}
