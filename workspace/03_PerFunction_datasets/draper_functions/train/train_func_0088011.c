do_com_for(char *str)
{
    AD             *fo;
    char           *st;
    char           *co;
    char           *p;
    char           *eq;
    struct hash_struct *hs;
    st = find_string(str, "$(");
    st += 2;
    READ_SPACES(st);
    co = strchr(st, ')');
    *(co++) = 0;
    eq = strchr(co, '=');
    if (eq) {
        char           *to;
        *(eq++) = 0;
        READ_SPACES(eq);
        to = find_string(eq, "TO");
        if (!to) {
            print_error("TO not found in FOR :( FOR $(i) = a TO b )");
            return 1;
        }
        *to = 0;
        to += 2;
        READ_SPACES(to);
        if (do_com_for_add(gl->pc)) return 1;
        gl->pc->fd->forval = atol(eq);
        gl->pc->fd->forend = atol(to);
        if (gl->pc->fd->forval > gl->pc->fd->forend) {
            gl->nextpc = gl->pc->NEXT->next;
            return do_com_for_sub(gl->pc);
        }
        p = (char *) read_hash_local(st, &hs);
        if (!p) {
            printf_error("Undefined Ident '%s' in FOR (use CREATE first)", st);
            return 1;
        }
        sprintf(string_buf, "%li", gl->pc->fd->forval);
        write_hash(hs, st, string_buf);
        gl->pc->fd->forstr = strdup(st);
    } else {
        p = strrchr(st, '/');
        if (p)
            str = p + 1;
        else
            str = st;
        if (p) {
            fo = aisc_find_var_hier(gl->cursor, st, 0, 0, 0);
        } else {
            fo = aisc_find_var_hier(gl->cursor, st, 0, 1, 0);
        }
        if (!fo) {
            gl->nextpc = gl->pc->NEXT->next;
            return 0;
        }
        do_com_for_add(gl->pc);
        gl->pc->fd->forstr = strdup(str);
        gl->pc->fd->forcursor = gl->cursor;
        gl->cursor = fo;
    }
    return 0;
}
