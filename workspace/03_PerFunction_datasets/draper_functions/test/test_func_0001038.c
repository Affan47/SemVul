encode_row_count(SQLINTEGER num_of_rows,
				      db_state *state)
{
    db_result_msg msg;
    int index;

    index = 0;
    ei_encode_version(NULL, &index);
    ei_encode_tuple_header(NULL, &index, 2);
    ei_encode_atom(NULL, &index, "ok");
    if(num_of_rows == -1)
    {
	ei_encode_atom(NULL, &index, "undefined");
    } else {
	ei_encode_long(NULL, &index, num_of_rows);
    }
    msg.length = index;
    msg.buffer = (byte *)safe_malloc(index);
    msg.dyn_alloc = FALSE;

    index = 0;
    ei_encode_version((char *)msg.buffer, &index);
    ei_encode_tuple_header((char *)msg.buffer, &index, 2);
    ei_encode_atom((char *)msg.buffer, &index, "ok");

    if(num_of_rows == -1)
    {
	ei_encode_atom((char *)msg.buffer, &index, "undefined");
    } else {
	ei_encode_long((char *)msg.buffer, &index, num_of_rows);
    }
    return msg;
}
