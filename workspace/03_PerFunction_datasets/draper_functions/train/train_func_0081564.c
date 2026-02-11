poly_control(audio_patch_t *p, audio_channel_t *c, int tag,
		int ctl, int arg)
{
	int mask;
	if(AVT_ALL == tag)
		mask = tag = 0;
	else
		mask = -1;

	switch(ctl)
	{
	  case ACC_GROUP:
	  case ACC_PRIORITY:
	  case ACC_PATCH:
		break;
	  case ACC_PRIM_BUS:
	  {
		audio_voice_t *v = chan_get_first_voice(c);
		while(v)
		{
			if((v->tag & mask) == tag)
				v->c[VC_PRIM_BUS] = arg;
			v = chan_get_next_voice(v);
		}
		break;
	  }
	  case ACC_SEND_BUS:
	  {
		audio_voice_t *v = chan_get_first_voice(c);
		while(v)
		{
			if((v->tag & mask) == tag)
				v->c[VC_SEND_BUS] = arg;
			v = chan_get_next_voice(v);
		}
		break;
	  }
	  case ACC_PITCH:
	  {
		audio_voice_t *v = chan_get_first_voice(c);
		while(v)
		{
			int pitch;
			if((v->tag & mask) == tag)
			{
				pitch = c->ctl[ACC_PITCH];
				pitch += v->closure.pitch;
				pitch -= 60<<16;
				(void)aev_sendi1(&v->port, 0, VE_SET,
						VC_PITCH, pitch);
			}
			v = chan_get_next_voice(v);
		}
		break;
	  }
	  case ACC_PAN:
	  case ACC_VOLUME:
	  case ACC_SEND:
	  {
		audio_voice_t *v = chan_get_first_voice(c);
		while(v)
		{
			if((v->tag & mask) == tag)
			{


				__env_control_recalc(p, c, v);
			}
			v = chan_get_next_voice(v);
		}
		break;
	  }
	}
}
