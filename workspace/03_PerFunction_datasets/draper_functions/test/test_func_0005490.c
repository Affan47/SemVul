delete_echo_channel(struct hdp_channel *chan)
{
	GError *err = NULL;

	if (!chan->dev->mcl_conn) {
		error("Echo channel cannot be deleted: mcl closed");
		return;
	}

	if (mcap_delete_mdl(chan->mdl, delete_echo_channel_cb,
				hdp_channel_ref(chan),
				(GDestroyNotify) hdp_channel_unref, &err))
		return;

	hdp_channel_unref(chan);
	error("Error deleting the echo channel: %s", err->message);
	g_error_free(err);


}
