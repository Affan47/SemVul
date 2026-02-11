s_flush(synth_t *s)
{

  if (!text_thread_active) return 0;

  TEXT_LOCK_NI;
  text_synthpos = text_tail;
  TEXT_UNLOCK_NI;

  if (!wave_thread_active)
  {
	es_log(2, "es_flush: creating play thread");
	WAVE_LOCK_NI;
	wave_thread_active = 1;
	ac_synthpos = ac_tail;
	pthread_create(&wave_thread, &ta, play, s);
	WAVE_UNLOCK_NI;
  }
  else
  {
	WAVE_LOCK_NI;
	if (ac_synthpos < ac_tail)
	{
	  ac_synthpos = ac_tail;
	  pthread_cond_signal(&wave_condition);
	}
	WAVE_UNLOCK_NI;
  }
  return 0;
}
