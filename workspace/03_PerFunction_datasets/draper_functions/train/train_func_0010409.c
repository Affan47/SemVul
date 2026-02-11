assignable_gen(struct parser_params *parser, ID id, NODE *val)
#endif
{
#ifdef RIPPER
    ID id = get_id(lhs);
# define assignable_result(x) get_value(lhs)
# define parser_yyerror(parser, x) dispatch1(assign_error, lhs)
#else
# define assignable_result(x) (x)
#endif
    if (!id) return assignable_result(0);
    if (id == keyword_self) {
	yyerror("Can't change the value of self");
    }
    else if (id == keyword_nil) {
	yyerror("Can't assign to nil");
    }
    else if (id == keyword_true) {
	yyerror("Can't assign to true");
    }
    else if (id == keyword_false) {
	yyerror("Can't assign to false");
    }
    else if (id == keyword__FILE__) {
	yyerror("Can't assign to __FILE__");
    }
    else if (id == keyword__LINE__) {
	yyerror("Can't assign to __LINE__");
    }
    else if (id == keyword__ENCODING__) {
	yyerror("Can't assign to __ENCODING__");
    }
    else if (is_local_id(id)) {
	if (dyna_in_block()) {
	    if (dvar_curr(id)) {
		return assignable_result(NEW_DASGN_CURR(id, val));
	    }
	    else if (dvar_defined(id)) {
		return assignable_result(NEW_DASGN(id, val));
	    }
	    else if (local_id(id)) {
		return assignable_result(NEW_LASGN(id, val));
	    }
	    else {
		dyna_var(id);
		return assignable_result(NEW_DASGN_CURR(id, val));
	    }
	}
	else {
	    if (!local_id(id)) {
		local_var(id);
	    }
	    return assignable_result(NEW_LASGN(id, val));
	}
    }
    else if (is_global_id(id)) {
	return assignable_result(NEW_GASGN(id, val));
    }
    else if (is_instance_id(id)) {
	return assignable_result(NEW_IASGN(id, val));
    }
    else if (is_const_id(id)) {
	if (!in_def && !in_single)
	    return assignable_result(NEW_CDECL(id, val, 0));
	yyerror("dynamic constant assignment");
    }
    else if (is_class_id(id)) {
	return assignable_result(NEW_CVASGN(id, val));
    }
    else {
	compile_error(PARSER_ARG "identifier %s is not valid to set", rb_id2name(id));
    }
    return assignable_result(0);
#undef assignable_result
#undef parser_yyerror
}
