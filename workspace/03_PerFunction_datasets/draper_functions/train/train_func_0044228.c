sgen_bridge_register_finalized_object (GCObject *obj)
{
	bridge_processor.register_finalized_object (obj);
	if (compare_bridge_processors ())
		compare_to_bridge_processor.register_finalized_object (obj);
}
