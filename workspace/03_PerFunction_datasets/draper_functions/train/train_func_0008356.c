sieve_parse(sieve_script_t *script, FILE *f)
{
    commandlist_t *t;

    parse_script = script;
    yyrestart(f);
    if (yyparse()) {
	t = NULL;
    } else {
	t = ret;
    }
    ret = NULL;
    return t;
}
