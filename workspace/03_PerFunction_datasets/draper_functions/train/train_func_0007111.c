get_and_clean_tcp_connection_by_id(ur_map *map, tcp_connection_id id)
{
	if(map) {
		ur_map_value_type t = 0;
		if (ur_map_get(map, (ur_map_key_type)id, &t) && t) {
			ur_map_del(map, (ur_map_key_type)id,NULL);
			return (tcp_connection*)t;
		}
	}
	return NULL;
}
