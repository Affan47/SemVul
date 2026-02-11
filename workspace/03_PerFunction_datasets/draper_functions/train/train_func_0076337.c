fstate_src_free(void *that)
{
    fstate_src_ty   *this_thing;

    this_thing = (fstate_src_ty *)that;
    if (!this_thing)
	return;
    this_thing->reference_count--;
    assert(this_thing->reference_count >= 0);
    if (this_thing->reference_count > 0)
	return;
    trace(("fstate_src_free(this_thing = %08lX)\n{\n", (long)this_thing));
    if (this_thing->errpos)
    {
	str_free(this_thing->errpos);
	this_thing->errpos = 0;
    }
    str_free(this_thing->file_name);
    str_free(this_thing->uuid);
    history_version_type.free(this_thing->edit);
    str_free(this_thing->edit_number);
    history_version_type.free(this_thing->edit_origin);
    str_free(this_thing->edit_number_origin);
    history_version_type.free(this_thing->edit_origin_new);
    str_free(this_thing->edit_number_origin_new);
    fingerprint_free(this_thing->file_fp);
    fingerprint_free(this_thing->diff_file_fp);
    fingerprint_free(this_thing->idiff_file_fp);
    fstate_src_architecture_times_list_free(this_thing->architecture_times);
    str_free(this_thing->move);
    fstate_src_test_list_free(this_thing->test);
    metric_list_type.free(this_thing->metrics);
    attributes_list_type.free(this_thing->attribute);
    mem_free(this_thing);
    trace(("}\n"));
}
