print_destructor (Variable *v)
{
	const char *root;

	if(v->destructor == NULL)
		return;

	if(v->scope == PRIVATE_SCOPE)
		root = "self->_priv";
	else
		root = "self";

	if(v->destructor_simple) {
		if(v->destructor_line > 0)
			out_addline_infile(out, v->destructor_line);

		if (for_cpp) {
			out_printf(out, "\tif(%s->%s) { "
				   "(reinterpret_cast<void (*)(void *)>(%s)) ((gpointer)%s->%s); "
				   "%s->%s = NULL; }\n",
				   root, v->id, v->destructor, root, v->id,
				   root, v->id);
		} else {
			out_printf(out, "\tif(%s->%s) { "
				   "%s ((gpointer) %s->%s); "
				   "%s->%s = NULL; }\n",
				   root, v->id, v->destructor, root, v->id,
				   root, v->id);
		}

		if(v->destructor_line > 0)
			out_addline_outfile(out);
	} else {
		out_printf(out, "#define %s (%s->%s)\n", v->id, root, v->id);
		out_printf(out, "#define VAR %s\n", v->id);
		out_printf(out, "\t{\n");
		if(v->destructor_line > 0)
			out_addline_infile(out, v->destructor_line);

		out_printf(out, "\t%s}\n", v->destructor);

		if(v->destructor_line > 0)
			out_addline_outfile(out);
		out_printf(out, "\tmemset(&(%s), 0, sizeof(%s));\n",
			   v->id, v->id);
		out_printf(out, "#undef VAR\n");
		out_printf(out, "#undef %s\n", v->id);
	}
}
