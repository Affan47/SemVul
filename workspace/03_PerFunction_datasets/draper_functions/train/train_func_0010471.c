assemble(struct membuf *source, struct membuf *dest)
{
    int val;

    LOG_INIT_CONSOLE(LOG_NORMAL);
    parse_init();
    yydebug = 0;
    asm_src_buffer_push(source);
    vec_init(asm_atoms, sizeof(struct atom*));
    val = yyparse();
    if(val == 0)
    {
        output_atoms(dest, asm_atoms);
    }
    parse_free();
    vec_free(asm_atoms, NULL);
    yycleanup();
    LOG_FREE;

    return val;
}
