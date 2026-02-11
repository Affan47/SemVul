rec_match_fn(void *data, node_rec_t *rec)
{
	struct rec_op_data *op_data = data;

	if (!__iscsi_match_session(op_data->match_rec, rec->name,
				   rec->conn[0].address, rec->conn[0].port,
				   &rec->iface, rec->session.sid))
		return -1;
	return op_data->fn(op_data->data, rec);
}
