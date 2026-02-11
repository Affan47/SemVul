history_version_write_xml(const output::pointer &fp, const char *name, history_version_ty *this_thing)
{
    if (!this_thing)
	return;
    trace(("history_version_write_xml(name = \"%s\", this_thing = %08lX)\n{\n", name, (long)this_thing));
    assert(name);
    assert(((history_version_ty *)this_thing)->reference_count > 0);
    trace(("rc = %ld;\n", ((history_version_ty *)this_thing)->reference_count));
    assert(name);
    fp->fputc('<');
    fp->fputs(name);
    fp->fputs(">\n");
    string_write_xml(fp, "revision", this_thing->revision);
    history_version_encoding_write_xml(fp, "encoding", this_thing->encoding, 0);
    fp->fputs("</");
    fp->fputs(name);
    fp->fputs(">\n");
}
