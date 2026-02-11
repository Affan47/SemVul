rc_variable_list_get_writers_one_reader(
	struct rc_list * var_list,
	unsigned int src_type,
	void * src)
{
	struct rc_list * writer_list =
		rc_variable_list_get_writers(var_list, src_type, src);
	struct rc_list * reader_list =
		rc_variable_readers_union(writer_list->Item);
	if (rc_list_count(reader_list) > 1) {
		return NULL;
	} else {
		return writer_list;
	}
}
