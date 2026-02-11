connkill_real(aim_session_t *sess, aim_conn_t **deadconn)
{

	aim_rxqueue_cleanbyconn(sess, *deadconn);
	aim_tx_cleanqueue(sess, *deadconn);

	if ((*deadconn)->fd != -1)
		aim_conn_close(*deadconn);


	if ((*deadconn)->priv)
		free((*deadconn)->priv);


	if ((*deadconn)->type == AIM_CONN_TYPE_CHAT)
		aim_conn_kill_chat(sess, *deadconn);

	if ((*deadconn)->inside) {
		aim_conn_inside_t *inside =
			(aim_conn_inside_t *)(*deadconn)->inside;

		connkill_snacgroups(&inside->groups);
		connkill_rates(&inside->rates);

		free(inside);
	}

	free(*deadconn);
	*deadconn = NULL;

	return;
}
