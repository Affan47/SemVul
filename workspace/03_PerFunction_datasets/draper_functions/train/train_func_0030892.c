ndmp_sxa_tape_mtio (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn)
{
	ndmp9_error		error;
	ndmp9_tape_mtio_op	tape_op;
	int			will_write = 0;
	unsigned long		resid = 0;

      NDMS_WITH(ndmp9_tape_mtio)

	switch (request->tape_op) {
	default:
		NDMADR_RAISE_ILLEGAL_ARGS("tape_op");

	case NDMP9_MTIO_EOF:
		will_write = 1;
		tape_op = NDMP9_MTIO_EOF;
		break;

	case NDMP9_MTIO_FSF:
	case NDMP9_MTIO_BSF:
	case NDMP9_MTIO_FSR:
	case NDMP9_MTIO_BSR:
	case NDMP9_MTIO_REW:
	case NDMP9_MTIO_OFF:
		tape_op = request->tape_op;
		break;
	}

	error = tape_op_ok (sess, will_write);
	if (error != NDMP9_NO_ERR) {
		NDMADR_RAISE(error, "!tape_op_ok");
	}

	error = ndmos_tape_mtio (sess, tape_op, request->count, &resid);

	reply->error = error;
	reply->resid_count = resid;

	return 0;
      NDMS_ENDWITH
}
