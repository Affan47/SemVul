gst_avdtp_sink_bluetooth_recvmsg_fd(GstAvdtpSink *sink)
{
	int err, ret;

	ret = bt_audio_service_get_data_fd(
			g_io_channel_unix_get_fd(sink->server));

	if (ret < 0) {
		err = -errno;
		GST_ERROR_OBJECT(sink, "Unable to receive fd: %s (%d)",
				strerror(-err), -err);
		return err;
	}

	sink->stream = g_io_channel_unix_new(ret);
	g_io_channel_set_encoding(sink->stream, NULL, NULL);
	GST_DEBUG_OBJECT(sink, "stream_fd=%d", ret);

	return 0;
}
