next_object(char *code, int *start, int *end, int *state)
{
    static const int STATE_EOL   = 1 << 1;
    static const int STATE_DOT   = 1 << 2;
    static const int STATE_QUOTE = 1 << 3;

    pobject result = NIL;

    switch (next_token(code, start, end)) {
    case TK_SYMBOL:
        result = symbol_intern_by_slice(code, *start, *end);
        break;
    case TK_NUMBER:
        result = gc_add( number_new_by_slice(code, *start, *end) );
        break;
    case TK_DOT:
        *state |= STATE_DOT;
        result = next_object(code, start, end, state);
        break;
    case TK_QUOTE:
        *state |= STATE_QUOTE;
        result = next_object(code, start, end, state);
        break;
    case TK_PAREN_OPEN:
        for (;;) {
            int entry_state = 0;
            pobject entry = next_object(code, start, end, &entry_state);
            if (entry_state & STATE_EOL) {
                break;
            } else if (entry_state & STATE_DOT) {
                cons_list_last_cdr_set(&result, entry);
                break;
            } else {
                cons_list_append(&result, entry, 1);
            }
        }
        break;
    case TK_PAREN_CLOSE:
    case TK_EOF:
        *state |= STATE_EOL;
        break;
    }

    if (*state & STATE_QUOTE) {
        result = gc_add( cons_new( symbol_quote,
                    gc_add( cons_new( result, NIL ))));
        *state = *state & ~STATE_QUOTE;
    }

    return result;
}
