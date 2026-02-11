ai_big_strafe_position()
{
	ship_info *sip;
	ai_info	*aip;
	sip = &Ship_info[Ships[Pl_objp->instance].ship_info_index];
	aip = &Ai_info[Ships[Pl_objp->instance].ai_index];


	if ((sip->can_glide == true) && !(aip->ai_flags & AIF_KAMIKAZE) && (frand() < aip->ai_glide_strafe_percent)) {
		aip->submode = AIS_STRAFE_GLIDE_ATTACK;
		aip->submode_parm1 = 0;
	} else {
		aip->submode = AIS_STRAFE_ATTACK;
	}
	aip->submode_start_time = Missiontime;
}
