send_msg_data_check(int conn_num, void *data, int data_size)
{
	int opr, sizer;
	int err;

	if ((err = send_msg_data(conn_num, data, data_size)) < 0)
		return err;

	if ((err = receive_response(conn_num, &opr, &sizer)) < 0)
		return err;

	return 0;
}
