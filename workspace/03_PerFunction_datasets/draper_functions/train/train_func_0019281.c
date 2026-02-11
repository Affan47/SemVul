pc_need_status_point(struct map_session_data *sd,int type)
{
	int val = -1;

	nullpo_retr(-1, sd);

	switch(type) {
		case SP_STR: val = sd->status.str;  break;
		case SP_AGI: val = sd->status.agi;  break;
		case SP_VIT: val = sd->status.vit;  break;
		case SP_INT: val = sd->status.int_; break;
		case SP_DEX: val = sd->status.dex;  break;
		case SP_LUK: val = sd->status.luk;  break;
	}

	if(pc_is3rdclass(sd)) {
		if(pc_isbaby(sd) && val >= battle_config.third_baby_status_max)
			return 0;
		else if(val >= battle_config.third_status_max)
			return 0;
	} else if(sd->status.class_ == PC_CLASS_ESNV) {
		if(pc_isbaby(sd) && val >= battle_config.esnv_baby_status_max)
			return 0;
		else if(val >= battle_config.esnv_status_max)
			return 0;
	} else if(sd->status.class_ == PC_CLASS_KG || sd->status.class_ == PC_CLASS_OB) {
			if(val >= battle_config.ko_status_max)
				return 0;
	} else {
		if(pc_isbaby(sd) && val >= battle_config.baby_status_max)
			return 0;
		else if(val >= battle_config.max_parameter)
			return 0;
	}

	if(val < 0)
		val = -1;
	else if(val < 100)
		val = (val + 9) / 10 + 1;
	else if(battle_config.new_statusup_calc)
		val = 16 + (val / 5 - 20) * 4;
	else
		val = (val + 9) / 10 + 1;

	return val;
}
