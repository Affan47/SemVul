IndexFromShapeId( ShapeId id )

{
    if( id == NullShapeId )
        return -1;

    LoadHeader();


    if( id == last_shapes_id )
        return last_shapes_index;


    if( id == last_shapes_id + 1
        && last_shapes_index + 1 >= shape_index_start
        && last_shapes_index + 1 < shape_index_start + (int) shape_index_ids.size() )
    {
        last_shapes_index++;
        last_shapes_id++;
        return last_shapes_index;
    }


    if( !shapeid_map_active )
    {
        PopulateShapeIdMap();
    }


    if( shapeid_map.count( id ) == 1 )
        return shapeid_map[id];

    return -1;
}
