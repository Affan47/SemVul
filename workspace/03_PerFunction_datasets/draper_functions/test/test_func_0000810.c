gen_template_import(const Symbol *s)
{
    FILE *f = get_code_file();

    if (template_flag == 0)
	return;

    gen_extern_stubs(f, s->gen_name);
}
