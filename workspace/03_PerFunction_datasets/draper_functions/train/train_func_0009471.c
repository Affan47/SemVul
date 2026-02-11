shadowing_lvar_gen(struct parser_params *parser, ID name)
{
    if (idUScore == name) return name;
    if (dyna_in_block()) {
	if (dvar_curr(name)) {
	    yyerror("duplicated argument name");
	}
	else if (dvar_defined_get(name) || local_id(name)) {
	    rb_warningS("shadowing outer local variable - %s", rb_id2name(name));
	    vtable_add(lvtbl->vars, name);
	    if (lvtbl->used) {
		vtable_add(lvtbl->used, (ID)ruby_sourceline | LVAR_USED);
	    }
	}
    }
    else {
	if (local_id(name)) {
	    yyerror("duplicated argument name");
	}
    }
    return name;
}
