fstate_free(void *that)
{
    fstate_ty	    *this_thing;

    this_thing = (fstate_ty *)that;
    if (!this_thing)
	return;
    this_thing->reference_count--;
    assert(this_thing->reference_count >= 0);
    if (this_thing->reference_count > 0)
	return;
    trace(("fstate_free(this_thing = %08lX)\n{\n", (long)this_thing));
    if (this_thing->errpos)
    {
	str_free(this_thing->errpos);
	this_thing->errpos = 0;
    }
    fstate_src_list_free(this_thing->src);
    mem_free(this_thing);
    trace(("}\n"));
}
