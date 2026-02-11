gzl_init_parse_state(struct gzl_parse_state *s,
                          struct gzl_bound_grammar *bg)
{
    s->offset.byte = 0;
    s->offset.line = 1;
    s->offset.column = 1;
    s->open_terminal_offset = s->offset;
    s->last_char_was_newline = false;
    s->bound_grammar = bg;
    RESIZE_DYNARRAY(s->parse_stack, 0);
    RESIZE_DYNARRAY(s->token_buffer, 0);


    s->max_stack_depth = 500;


    s->max_lookahead = 500;
}
