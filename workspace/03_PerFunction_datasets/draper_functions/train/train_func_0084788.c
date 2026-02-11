tstrslt_write_xml(const output::pointer &fp, tstrslt_ty *this_thing)
{
    if (!this_thing)
	return;
    trace(("tstrslt_write_xml(this_thing = %08lX)\n{\n", (long)this_thing));
    assert(((tstrslt_ty *)this_thing)->reference_count > 0);
    trace(("rc = %ld;\n", ((tstrslt_ty *)this_thing)->reference_count));
    fp->fputs("<tstrslt>\n");
    tstrslt_test_result_list_write_xml(fp, "test_result", this_thing->test_result);
    fp->fputs("</tstrslt>\n");
}
