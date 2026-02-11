__env_stop(audio_patch_t *p, audio_channel_t *c,
		audio_voice_t *v)
{
	patch_closure_t *clos = &v->closure;
	if(p->param[APP_ENV_T3] >= 0)
		return;

EGDBG(log_printf(D3LOG, "stop!\n");)
	switch (clos->env_state)
	{
	  case PES_START:
	  case PES_START2:
	  case PES_DELAY:
	  case PES_ATTACK:
	  case PES_HOLD:
	  case PES_DECAY:
		clos->queued_stop = 1;
		if(p->param[APP_ENV_SKIP])
		{
			clos->env_next = aev_timer;
			clos->env_state = PES_SUSTAIN;
		}
		break;
	  case PES_SUSTAIN:
	  case PES_RELEASE:
	  case PES_DEAD:
		break;
	  case PES_WAIT:
		clos->env_next = aev_timer;
		clos->env_state = PES_SUSTAIN;
		break;
	}
}
