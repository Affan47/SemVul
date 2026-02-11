rptidx_where_write(const output::pointer &fp, const char *name, rptidx_where_ty *this_thing)
{
    if (!this_thing)
	return;
    trace(("rptidx_where_write(name = \"%s\", this_thing = %08lX)\n{\n", name, (long)this_thing));
    assert(((rptidx_where_ty *)this_thing)->reference_count > 0);
    trace(("rc = %ld;\n", ((rptidx_where_ty *)this_thing)->reference_count));
    if (name)
    {
	fp->fputs(name);
	fp->fputs(" =\n");
    }
    fp->fputs("{\n");
    string_write(fp, "name", this_thing->name);
    string_write(fp, "description", this_thing->description);
    string_write(fp, "filename", this_thing->filename);
    fp->fputs("}");
    if (name)
	fp->fputs(";\n");
    trace(("}\n"));
}
