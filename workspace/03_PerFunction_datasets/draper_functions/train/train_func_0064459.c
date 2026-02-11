cstate_src_free(void *that)
{
    cstate_src_ty   *this_thing;

    this_thing = (cstate_src_ty *)that;
    if (!this_thing)
	return;
    this_thing->reference_count--;
    assert(this_thing->reference_count >= 0);
    if (this_thing->reference_count > 0)
	return;
    trace(("cstate_src_free(this_thing = %08lX)\n{\n", (long)this_thing));
    if (this_thing->errpos)
    {
	str_free(this_thing->errpos);
	this_thing->errpos = 0;
    }
    str_free(this_thing->file_name);
    str_free(this_thing->uuid);
    str_free(this_thing->edit_number);
    str_free(this_thing->move);
    attributes_list_type.free(this_thing->attribute);
    mem_free(this_thing);
    trace(("}\n"));
}
