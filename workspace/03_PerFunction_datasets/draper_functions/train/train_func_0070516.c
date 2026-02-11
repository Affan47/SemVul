liblo10k1_get_point_info(liblo10k1_connection_t *conn, int point_id, liblo10k1_point_info_t *out)
{
	int opr, sizer;
	int err;

	if ((err = send_request(*conn, FNC_GET_POINT_INFO, &point_id, sizeof(point_id))) < 0)
		return err;

	if ((err = receive_response(*conn, &opr, &sizer)) < 0)
		return err;

	if (sizer != sizeof(liblo10k1_point_info_t))
		return LD10K1_ERR_PROTOCOL;
	if ((err = receive_msg_data(*conn, out, sizer)) < 0)
		return LD10K1_ERR_PROTOCOL;

	if ((err = receive_response(*conn, &opr, &sizer)) < 0)
		return err;

	return 0;
}
