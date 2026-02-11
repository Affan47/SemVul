afterburners_start(object *objp)
{
	ship_info	*sip;
	ship			*shipp;
	float			percent_left;

	Assert( objp != NULL );

	if(objp->type == OBJ_OBSERVER)
		return;

	Assert( objp->type == OBJ_SHIP);
	Assert( objp->instance >= 0 && objp->instance < MAX_SHIPS );

	shipp = &Ships[objp->instance];
	Assert( shipp->ship_info_index >= 0 && shipp->ship_info_index < Num_ship_classes );
	sip = &Ship_info[shipp->ship_info_index];


	if (shipp->flags2 & SF2_AFTERBURNER_LOCKED)	{
		return;
	}

	if ( (objp->flags & OF_PLAYER_SHIP) && (objp == Player_obj) ) {
		unsigned int now;
		now = timer_get_milliseconds();

		if ( (now - Player_afterburner_start_time) < 1300 ) {
			snd_play( &Snds[ship_get_sound(objp, SND_ABURN_FAIL)] );
			return;
		}

		if ( objp->phys_info.flags & PF_AFTERBURNER_WAIT ){
			return;
		}
	}

	if ( objp->phys_info.flags & PF_AFTERBURNER_ON )	{
		return;
	}


	if (objp->phys_info.flags & PF_BOOSTER_ON)
		return;

	if ( !(sip->flags & SIF_AFTERBURNER) )	{
		return;
	}


	if ( (shipp->afterburner_fuel < MIN_AFTERBURNER_FUEL_TO_ENGAGE) && !MULTIPLAYER_CLIENT ) {
		if ( objp == Player_obj ) {
			snd_play( &Snds[ship_get_sound(objp, SND_ABURN_FAIL)] );
		}
		return;
	}

	objp->phys_info.flags |= PF_AFTERBURNER_ON;

	objp->phys_info.afterburner_decay = timestamp(ABURN_DECAY_TIME);

	percent_left = shipp->afterburner_fuel / sip->afterburner_fuel_capacity;


	model_anim_start_type(shipp, TRIGGER_TYPE_AFTERBURNER, ANIMATION_SUBTYPE_ALL, 1);

	if ( objp == Player_obj ) {
		Player_afterburner_start_time = timer_get_milliseconds();
		Player_disengage_timer = 1;
		Player_afterburner_vol = AFTERBURNER_DEFAULT_VOL;

		if ( percent_left > AFTERBURNER_PERCENT_FOR_LOOP_SND ) {
			Player_afterburner_loop_delay = timestamp(AFTERBURNER_LOOP_DELAY);
		}
		else {
			Player_afterburner_loop_delay = 0;
		}

		snd_play( &Snds[ship_get_sound(objp, SND_ABURN_ENGAGE)], 0.0f, 1.0f, SND_PRIORITY_MUST_PLAY );
		joy_ff_afterburn_on();
	} else {
		snd_play_3d( &Snds[ship_get_sound(objp, SND_ABURN_ENGAGE)], &objp->pos, &View_position, objp->radius );
	}

	objp->phys_info.flags |= PF_AFTERBURNER_WAIT;
}
