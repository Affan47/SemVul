sc_do_define()
{
    int c;

    skip_spaces();
    c = buffer_read_char();
    if (is_initial_identifier_char(c)) {
        ScmObj name;
        ScmObj args;
        ScmDString ds;
        is_force_identifier = TRUE;
        Scm_DStringInit(&ds);
        SCM_DSTRING_PUTB(&ds, (char) c);
        name = SCM_CDR(read_identifier(&ds));
        args = SCM_FALSE;
        if (buffer_peek_char() == '(') {
            buffer_next_char();
            args = SCM_NIL;
            skip_spaces();
            c = buffer_read_char();
            while (1) {
                if (c == ')') {
                    args = Scm_Reverse(args);
                    break;
                } else if (is_initial_identifier_char(c)) {
                    Scm_DStringInit(&ds);
                    SCM_DSTRING_PUTB(&ds, (char) c);
                    args = Scm_Cons(SCM_CDR(read_identifier(&ds)), args);
                    skip_spaces();
                    c = buffer_read_char();
                    continue;
                } else if (c == ',') {
                    skip_spaces();
                    c = buffer_read_char();
                    continue;
                } else {
                    goto finish;
                }
            }
        }
        enqueue_macro(name, args);
    }
finish:
    is_force_identifier = FALSE;
    skip_line();
}
