print_initializer(Method *m, Variable *v)
{
	char *root;

	if(v->glade_widget)
		return;

	if(v->initializer == NULL)
		return;

	if(v->scope == PRIVATE_SCOPE)
		root = g_strconcat(((FuncArg *)m->args->data)->name,
				   "->_priv", NULL);
	else
		root = g_strdup(((FuncArg *)m->args->data)->name);

	if(v->initializer_line > 0)
		out_addline_infile(out, v->initializer_line);

	if (v->initializer_simple)
		out_printf(out, "\t%s->%s = %s;\n",
		   root, v->id, v->initializer);
	else if (strcmp(v->id, "_glade_xml") == 0)


		out_printf(out,v->initializer, ((FuncArg *)m->args->data)->name);
	else
		out_printf(out, "%s", v->initializer);

	if(v->initializer_line > 0)
		out_addline_outfile(out);

	g_free(root);
}
