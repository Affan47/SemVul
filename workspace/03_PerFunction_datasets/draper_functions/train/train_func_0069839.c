snd_aw2_saa7146_define_it_playback_callback(unsigned int stream_number,
						 snd_aw2_saa7146_it_cb
						 p_it_callback,
						 void *p_callback_param)
{
	if (stream_number < NB_STREAM_PLAYBACK) {
		arr_substream_it_playback_cb[stream_number].p_it_callback =
		    (snd_aw2_saa7146_it_cb) p_it_callback;
		arr_substream_it_playback_cb[stream_number].p_callback_param =
		    (void *)p_callback_param;
	}
}
