decode_pcm8(SChannel *ch, s32 *out, int length)
{
	int oi;
	double pos, inc, len;
	if (!ch->buf8) return;

	pos = ch->pos; inc = ch->inc; len = ch->loopend;

	for(oi = 0; oi < length; oi++)
	{
		ch->output = ((s16)(s8)ch->buf8[(int)pos]) << 8;
#if 0
		if (dwChannelMute & (1 << ch->id))
		{
			out++;
			out++;
		}
		else
#endif
		{
			*(out++) += (ch->output * ch->volumel) >> VOL_SHIFT;
			*(out++) += (ch->output * ch->volumer) >> VOL_SHIFT;
		}
		pos += inc;
		if(pos >= len)
		{
			switch(ch->repeat)
			{
#if !DISABLE_XSF_TESTS
			case 0:
#endif
			case 1:
				pos += ch->looppos - len;
				break;
			default:
				stop_channel(ch);
				oi = length;
				break;
			}
		}
	}

	ch->pos = pos;
	return;
}
