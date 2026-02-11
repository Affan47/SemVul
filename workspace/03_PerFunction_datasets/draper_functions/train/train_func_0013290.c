map_id2sd(int id)
{
	struct block_list *bl;

	if(id > 0) {
		bl = (struct block_list *)numdb_search(id_db,id);
		if(bl && bl->type == BL_PC)
			return (struct map_session_data *)bl;
	}
	return NULL;
}
