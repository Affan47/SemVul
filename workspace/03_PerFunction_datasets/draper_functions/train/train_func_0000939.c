put_variable(const Variable *v, FILE *fp)
{
	out_printf(fp, "\t");
	print_type(fp, v->vtype, FALSE);
	out_printf(fp, "%s%s;", v->id,
		   v->vtype->postfix?
		   v->vtype->postfix:"");
	if(v->scope == PROTECTED_SCOPE)
		out_printf(fp, " /* protected */");
	out_printf(fp, "\n");
}
