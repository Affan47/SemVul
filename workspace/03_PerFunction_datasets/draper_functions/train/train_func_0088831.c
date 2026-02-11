cattr_write(const output::pointer &fp, cattr_ty *this_thing)
{
    if (!this_thing)
	return;
    trace(("cattr_write(this_thing = %08lX)\n{\n", (long)this_thing));
    assert(((cattr_ty *)this_thing)->reference_count > 0);
    trace(("rc = %ld;\n", ((cattr_ty *)this_thing)->reference_count));
    string_write(fp, "brief_description", this_thing->brief_description);
    string_write(fp, "description", this_thing->description);
    change_cause_write(fp, "cause", this_thing->cause, 1);
    boolean_write(fp, "test_exempt", this_thing->test_exempt, 1);
    boolean_write(fp, "test_baseline_exempt", this_thing->test_baseline_exempt, 1);
    boolean_write(fp, "regression_test_exempt", this_thing->regression_test_exempt, 1);
    cattr_architecture_list_write(fp, "architecture", this_thing->architecture);
    cattr_copyright_years_list_write(fp, "copyright_years", this_thing->copyright_years);
    string_write(fp, "version_previous", this_thing->version_previous);
    attributes_list_write(fp, "attribute", this_thing->attribute);
    trace(("}\n"));
}
