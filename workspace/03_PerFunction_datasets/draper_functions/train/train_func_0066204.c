listvar(
    const char *name,
    const char *value,
    int mflag,
    int exportflag,
    int shortflag)
{
    int i;
    ListEntry *node;
    Var *var;
    Pattern pname, pvalue;
    Vector vars = vector_init(1024);

    init_pattern_str(&pname, NULL);
    init_pattern_str(&pvalue, NULL);

    if (name)
        if (!init_pattern(&pname, name, mflag))
            goto listvar_end;

    if (value)
        if (!init_pattern(&pvalue, value, mflag))
            goto listvar_end;


    for (i = 0; i < var_table->size; i++) {
        if (var_table->bucket[i]) {
            for (node = var_table->bucket[i]->head; node; node = node->next) {
                var = (Var*)node->datum;
                if (!(var->flags & VARSET)) continue;
                if (exportflag >= 0 && !(var->flags & VAREXPORT) != !exportflag)                    continue;
                if (name && !patmatch(&pname, NULL, var->val.name)) continue;
                if (!var->val.sval) valstr(&var->val);
                if (value && !patmatch(&pvalue, var->val.sval, NULL)) continue;
		vector_add(&vars, node->datum);
            }
        }
    }

    vector_sort(&vars, strpppcmp);

    for (i = 0; i < vars.size; i++) {
	var = vars.ptrs[i];
	switch (shortflag) {
	case 1:  oputs(var->val.name);     break;
	case 2:  oputline(var->val.sval);  break;
	default:
	    oprintf("/set%s %s=%S",
		(var->flags & VAREXPORT) ? "env" : "",
		var->val.name, var->val.sval);
	}
    }
    vector_free(&vars);

listvar_end:
    free_pattern(&pname);
    free_pattern(&pvalue);
    return vars.size;
}
