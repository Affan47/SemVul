gen_assign_defval(const char *var, struct value *val)
{
    switch(val->type) {
    case stringvalue:
	fprintf(codefile, "if((%s = strdup(\"%s\")) == NULL)\nreturn ENOMEM;\n", var, val->u.stringvalue);
	break;
    case integervalue:
	fprintf(codefile, "%s = %lld;\n",
		var, (long long)val->u.integervalue);
	break;
    case booleanvalue:
	if(val->u.booleanvalue)
	    fprintf(codefile, "%s = TRUE;\n", var);
	else
	    fprintf(codefile, "%s = FALSE;\n", var);
	break;
    default:
	abort();
    }
}
