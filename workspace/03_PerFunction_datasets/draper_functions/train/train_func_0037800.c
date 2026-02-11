sample16s_handler (void)
{
	uae_u32 data0 = audio_channel[0].current_sample;
	uae_u32 data1 = audio_channel[1].current_sample;
	uae_u32 data2 = audio_channel[2].current_sample;
	uae_u32 data3 = audio_channel[3].current_sample;
	DO_CHANNEL_1 (data0, 0);
	DO_CHANNEL_1 (data1, 1);
	DO_CHANNEL_1 (data2, 2);
	DO_CHANNEL_1 (data3, 3);

	data0 &= audio_channel[0].adk_mask;
	data1 &= audio_channel[1].adk_mask;
	data2 &= audio_channel[2].adk_mask;
	data3 &= audio_channel[3].adk_mask;

	data0 += data3;
	data1 += data2;
	data2 = SBASEVAL16(1) + data0;
	data2 = FINISH_DATA (data2, 15);
	data3 = SBASEVAL16(1) + data1;
	data3 = FINISH_DATA (data3, 15);
	set_sound_buffers ();
	put_sound_word_left (data2);
	put_sound_word_right (data3);
	check_sound_buffers ();
}
