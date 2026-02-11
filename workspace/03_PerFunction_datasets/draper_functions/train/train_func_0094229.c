make_serialized_lwgeom(LWGEOM_PARSER_RESULT *lwg_parser_result)
{
	uchar* out_c;
	output_state out;
	tuple* cur;

	LWDEBUG(2, "make_serialized_lwgeom");


	out_c = (uchar*)local_malloc(the_geom.alloc_size);
	out.pos = out_c;
	cur = the_geom.first ;

	while(cur){
		cur->of(cur,&out);
		cur=cur->next;
	}


	lwg_parser_result->serialized_lwgeom = out_c;
	lwg_parser_result->size = the_geom.alloc_size;

	return;
}
