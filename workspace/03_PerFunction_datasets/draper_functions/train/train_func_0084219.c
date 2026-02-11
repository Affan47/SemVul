hermon_fill_ud_send_wqe ( struct ib_device *ibdev,
			  struct ib_queue_pair *qp __unused,
			  struct ib_address_vector *dest,
			  struct io_buffer *iobuf,
			  union hermon_send_wqe *wqe ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );

	MLX_FILL_1 ( &wqe->ud.ctrl, 1, ds,
		     ( ( offsetof ( typeof ( wqe->ud ), data[1] ) / 16 ) ) );
	MLX_FILL_1 ( &wqe->ud.ctrl, 2, c, 0x03  );
	MLX_FILL_2 ( &wqe->ud.ud, 0,
		     ud_address_vector.pd, HERMON_GLOBAL_PD,
		     ud_address_vector.port_number, ibdev->port );
	MLX_FILL_2 ( &wqe->ud.ud, 1,
		     ud_address_vector.rlid, dest->lid,
		     ud_address_vector.g, dest->gid_present );
	MLX_FILL_1 ( &wqe->ud.ud, 2,
		     ud_address_vector.max_stat_rate, hermon_rate ( dest ) );
	MLX_FILL_1 ( &wqe->ud.ud, 3, ud_address_vector.sl, dest->sl );
	memcpy ( &wqe->ud.ud.u.dwords[4], &dest->gid, sizeof ( dest->gid ) );
	MLX_FILL_1 ( &wqe->ud.ud, 8, destination_qp, dest->qpn );
	MLX_FILL_1 ( &wqe->ud.ud, 9, q_key, dest->qkey );
	MLX_FILL_1 ( &wqe->ud.data[0], 0, byte_count, iob_len ( iobuf ) );
	MLX_FILL_1 ( &wqe->ud.data[0], 1, l_key, hermon->lkey );
	MLX_FILL_H ( &wqe->ud.data[0], 2,
		     local_address_h, virt_to_bus ( iobuf->data ) );
	MLX_FILL_1 ( &wqe->ud.data[0], 3,
		     local_address_l, virt_to_bus ( iobuf->data ) );
	return HERMON_OPCODE_SEND;
}
