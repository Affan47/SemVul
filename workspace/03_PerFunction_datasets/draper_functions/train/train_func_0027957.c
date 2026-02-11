gen_include()
    const
{
    indent_putchar('\n');
    indent_printf("#ifndef %s_DEF\n", def_name().c_str());
    indent_printf("#define %s_DEF\n", def_name().c_str());
    indent_printf("\n");
    int bit = 0;
    size_t j;
    for (j = 0; j < nelements; ++j)
    {
	indent_printf
	(
	    "#define\t%s_%s_mask\t",
	    def_name().c_str(),
	    element[j].name.c_str()
	);
	if (element[j].etype->has_a_mask())
	    indent_printf("((unsigned long)1 << %d)", bit++);
	else
	    indent_printf("((unsigned long)0)");
	indent_printf("\n");
    }
    indent_printf("\n");
    indent_printf("struct %s_ty\n", def_name().c_str());
    indent_printf("{\n");


    indent_printf("long\1reference_count;\n");
    indent_printf("unsigned long\1mask;\n");
    indent_printf("string_ty\1*errpos;\n");

    for (j = 0; j < nelements; ++j)
    {
	element_ty *ep = &element[j];
	ep->etype->gen_include_declarator(ep->name, false);
    }
    indent_printf("};\n");
    indent_printf("#endif // %s_DEF\n", def_name().c_str());

    indent_putchar('\n');
    indent_printf("extern meta_type %s_type;\n", def_name().c_str());

    indent_putchar('\n');
    if (toplevel_flag)
    {
	indent_printf
	(
    	    "void %s_write(const output::pointer &fp, %s_ty *value);\n",
    	    def_name().c_str(),
    	    def_name().c_str()
	);
	indent_printf
	(
    	    "void %s_write_xml(const output::pointer &fp, %s_ty *value);\n",
    	    def_name().c_str(),
    	    def_name().c_str()
	);
    }
    else
    {
	indent_printf
	(
    	    "void %s_write(const output::pointer &fp, const char *name, "
                "%s_ty *value);\n",
    	    def_name().c_str(),
    	    def_name().c_str()
	);
	indent_printf
	(
    	    "void %s_write_xml(const output::pointer &fp, const char *name, "
                "%s_ty *value);\n",
    	    def_name().c_str(),
    	    def_name().c_str()
	);
    }
    indent_printf
    (
	"%s_ty *%s_copy(%s_ty *);\n",
	def_name().c_str(),
	def_name().c_str(),
	def_name().c_str()
    );
    indent_printf
    (
	"%s_ty *%s_clone(%s_ty *);\n",
	def_name().c_str(),
	def_name().c_str(),
	def_name().c_str()
    );
    indent_printf("#ifdef DEBUG\n");
    indent_printf
    (
	"void %s_trace_real(const char *name, const %s_ty *value);\n",
	def_name().c_str(),
	def_name().c_str()
    );
    indent_printf
    (
	"#define %s_trace(x) ((void)(trace_pretest_ && (trace_where_, "
	    "%s_trace_real(trace_stringize(x), x), 0)))\n",
	def_name().c_str(),
	def_name().c_str()
    );
    indent_printf("#else\n");
    indent_printf("#define %s_trace(x)\n", def_name().c_str());
    indent_printf("#endif\n");
}
