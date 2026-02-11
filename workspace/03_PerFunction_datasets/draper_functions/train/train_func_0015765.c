gf_audio_input_release_frame(void *callback, u32 nb_bytes)
{
	GF_AudioInput *ai = (GF_AudioInput *) callback;
	if (!ai->stream) return;
	gf_mo_release_data(ai->stream, nb_bytes, 1);
	ai->need_release = 0;
}
