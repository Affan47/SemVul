print_method_body (Method *m, gboolean pre, gboolean unused_self)
{
	out_printf(out, "{\n");
	if (m->line_no > 0)
		out_addline_outfile(out);
	out_printf(out, "#define __GOB_FUNCTION__ \"%s::%s\"\n",
		   ((Class *)class)->otype,
		   m->id);
	if (pre)
		print_preconditions(m);

	if ( ! pre &&
	     unused_self &&
	    (no_gnu || for_cpp) &&
	    m->args != NULL &&
	    ((FuncArg *)(m->args->data))->name != NULL &&
	    strcmp (((FuncArg *)(m->args->data))->name, "self") == 0) {
		out_printf (out, "\tif (&self) { ; }\n");
	}


	if(m->cbuf) {
		out_printf(out, "{\n");
		if(m->ccode_line>0)
			out_addline_infile(out, m->ccode_line);
		out_printf(out, "\t%s}", m->cbuf);
	}


	out_printf(out, "}\n");

	if(m->cbuf)
		out_addline_outfile(out);
	out_printf(out, "#undef __GOB_FUNCTION__\n");
}
