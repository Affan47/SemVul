aim_tx_enqueue(aim_session_t *sess, aim_frame_t *fr)
{


	if (fr && fr->conn && (fr->conn->status & AIM_CONN_STATUS_INPROGRESS)) {
		return aim_tx_enqueue__queuebased(sess, fr);
	}

	return (*sess->tx_enqueue) (sess, fr);
}
