cue_parser_new(CueMemPool *pool)
{
    CueParser *parser = cue_mem_pool_alloc(pool, sizeof *parser);
    if (parser == NULL) return NULL;
    parser->pool         = pool;
    parser->module       = _cue_parser_module;
    parser->use          = _cue_parser_use;
    parser->func_decl    = _cue_parser_func_decl;
    parser->class_decl   = _cue_parser_class_decl;
    parser->assign       = _cue_parser_assign;
    parser->get_attr     = _cue_parser_get_attr;
    parser->call         = _cue_parser_call;
    parser->name         = _cue_parser_name;
    parser->string       = _cue_parser_string;
    parser->integer      = _cue_parser_integer;
    parser->boolean      = _cue_parser_boolean;
    parser->push_expr    = _cue_parser_push_expr;
    parser->pop_expr     = _cue_parser_pop_expr;
    parser->expr_stack   = cue_list_new(pool);
    if (parser->expr_stack == NULL) return NULL;
    parser->stmt_stack   = cue_list_new(pool);
    if (parser->stmt_stack == NULL) return NULL;
    return parser;
}
