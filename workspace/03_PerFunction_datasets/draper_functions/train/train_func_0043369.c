slapi_delete_internal(const char *idn, LDAPControl **controls, int dummy)
{
    Slapi_PBlock	pb;
    Slapi_PBlock    *result_pb;
    int             opresult;

    pblock_init (&pb);

    slapi_delete_internal_set_pb (&pb, idn, controls, NULL, plugin_get_default_component_id(), 0);

	delete_internal_pb (&pb);

	result_pb = slapi_pblock_new();
	if (result_pb)
	{
		slapi_pblock_get(&pb, SLAPI_PLUGIN_INTOP_RESULT, &opresult);
		slapi_pblock_set(result_pb, SLAPI_PLUGIN_INTOP_RESULT, &opresult);
	}
	pblock_done(&pb);

    return result_pb;
}
