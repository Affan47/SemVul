read_file(File* filePtr)
{
	FileReader r;
	FileReaderVisitor v;

	if (!r.init(filePtr))
		return 0;

	r.check_record_size(169);
	v.init(&r);
	visit_unit(&v, this);

	if (!r.good())
		return 0;

	r.deinit();


	if( result_node_array )
	{
		result_node_array = (ResultNode*) mem_add( sizeof(ResultNode) * result_node_count );

		if( !filePtr->file_read( result_node_array, sizeof(ResultNode) * result_node_count ) )
			return 0;
	}


	if(way_point_array)
	{
		way_point_array = (ResultNode*) mem_add(sizeof(ResultNode) * way_point_array_size);

		if(!filePtr->file_read(way_point_array, sizeof(ResultNode)*way_point_array_size))
			return 0;
	}


	if( team_info )
	{
		team_info = (TeamInfo*) mem_add( sizeof(TeamInfo) );

		if( !filePtr->file_read( team_info, sizeof(TeamInfo) ) )
			return 0;
	}


	sprite_info       = sprite_res[sprite_id];

	sprite_info->load_bitmap_res();


   return 1;
}
