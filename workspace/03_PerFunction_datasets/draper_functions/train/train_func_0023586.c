SN76477_enable_w(int chip, int data)
{
	struct SN76477 *sn = sn76477[chip];

	CHECK_CHIP_NUM_AND_RANGE(1,SN76477_enable_w);

	if( data == sn->enable )
		return;
	stream_update(sn->channel, 0);
	sn->enable = data;
	sn->envelope_state = data;

	timer_adjust(sn->envelope_timer, TIME_NEVER, chip, 0);
	timer_adjust(sn->oneshot_timer, TIME_NEVER, chip, 0);

	if( sn->enable == 0 )
	{
		switch( sn->envelope )
		{
		case 0:
			if( sn->vco_res > 0 && sn->vco_cap > 0 )
				timer_adjust(sn->envelope_timer, TIME_IN_HZ(0.64/(sn->vco_res * sn->vco_cap)), chip, TIME_IN_HZ(0.64/(sn->vco_res * sn->vco_cap)));
			else
				oneshot_envelope_cb(chip);
			break;
		case 1:
			oneshot_envelope_cb(chip);
			if (sn->oneshot_time > 0)
				timer_adjust(sn->oneshot_timer, sn->oneshot_time, chip, 0);
			break;
		case 2:
			sn->vol = VMAX;
			break;
		default:

			if( sn->vco_res > 0 && sn->vco_cap > 0 )
				timer_adjust(sn->envelope_timer, TIME_IN_HZ(0.64/(sn->vco_res * sn->vco_cap)/2), chip, TIME_IN_HZ(0.64/(sn->vco_res * sn->vco_cap)/2));
			else
				oneshot_envelope_cb(chip);
			break;
		}
	}
	else
	{
		switch( sn->envelope )
		{
		case 0:
			if( sn->vco_res > 0 && sn->vco_cap > 0 )
				timer_adjust(sn->envelope_timer, TIME_IN_HZ(0.64/(sn->vco_res * sn->vco_cap)), chip, TIME_IN_HZ(0.64/(sn->vco_res * sn->vco_cap)));
			else
				oneshot_envelope_cb(chip);
			break;
		case 1:
			oneshot_envelope_cb(chip);
			break;
		case 2:
			sn->vol = VMIN;
			break;
		default:

			if( sn->vco_res > 0 && sn->vco_cap > 0 )
				timer_adjust(sn->envelope_timer, TIME_IN_HZ(0.64/(sn->vco_res * sn->vco_cap)/2), chip, TIME_IN_HZ(0.64/(sn->vco_res * sn->vco_cap)/2));
			else
				oneshot_envelope_cb(chip);
			break;
		}
	}
	LOG(1,("SN76477 #%d: ENABLE line %d [%s]\n", chip, sn->enable, sn->enable ? "Inhibited" : "Enabled" ));
}
