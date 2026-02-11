ibuf_new_search_tuple_build(

	ulint		space,
	ulint		page_no,
	mem_heap_t*	heap)
{
	dtuple_t*	tuple;
	dfield_t*	field;
	byte*		buf;

	ut_a(trx_sys_multiple_tablespace_format);

	tuple = dtuple_create(heap, IBUF_REC_FIELD_METADATA);


	field = dtuple_get_nth_field(tuple, IBUF_REC_FIELD_SPACE);

	buf = mem_heap_alloc(heap, 4);

	mach_write_to_4(buf, space);

	dfield_set_data(field, buf, 4);


	field = dtuple_get_nth_field(tuple, IBUF_REC_FIELD_MARKER);

	buf = mem_heap_alloc(heap, 1);

	mach_write_to_1(buf, 0);

	dfield_set_data(field, buf, 1);


	field = dtuple_get_nth_field(tuple, IBUF_REC_FIELD_PAGE);

	buf = mem_heap_alloc(heap, 4);

	mach_write_to_4(buf, page_no);

	dfield_set_data(field, buf, 4);

	dtuple_set_types_binary(tuple, IBUF_REC_FIELD_METADATA);

	return(tuple);
}
