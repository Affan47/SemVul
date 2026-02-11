sgen_debug_dump_heap (const char *type, int num, const char *reason)
{
	SgenPointerQueue *pinned_objects;
	LOSObject *bigobj;
	int i;

	if (!heap_dump_file)
		return;

	fprintf (heap_dump_file, "<collection type=\"%s\" num=\"%d\"", type, num);
	if (reason)
		fprintf (heap_dump_file, " reason=\"%s\"", reason);
	fprintf (heap_dump_file, ">\n");
#ifndef SGEN_WITHOUT_MONO
	fprintf (heap_dump_file, "<other-mem-usage type=\"mempools\" size=\"%ld\"/>\n", mono_mempool_get_bytes_allocated ());
#endif
	sgen_dump_internal_mem_usage (heap_dump_file);
	fprintf (heap_dump_file, "<pinned type=\"stack\" bytes=\"%zu\"/>\n", sgen_pin_stats_get_pinned_byte_count (PIN_TYPE_STACK));

	fprintf (heap_dump_file, "<pinned type=\"other\" bytes=\"%zu\"/>\n", sgen_pin_stats_get_pinned_byte_count (PIN_TYPE_OTHER));

	fprintf (heap_dump_file, "<pinned-objects>\n");
	pinned_objects = sgen_pin_stats_get_object_list ();
	for (i = 0; i < pinned_objects->next_slot; ++i)
		dump_object ((GCObject *)pinned_objects->data [i], TRUE);
	fprintf (heap_dump_file, "</pinned-objects>\n");

	sgen_dump_section (nursery_section, "nursery");

	major_collector.dump_heap (heap_dump_file);

	fprintf (heap_dump_file, "<los>\n");
	for (bigobj = los_object_list; bigobj; bigobj = bigobj->next)
		dump_object ((GCObject*)bigobj->data, FALSE);
	fprintf (heap_dump_file, "</los>\n");

	fprintf (heap_dump_file, "</collection>\n");
}
