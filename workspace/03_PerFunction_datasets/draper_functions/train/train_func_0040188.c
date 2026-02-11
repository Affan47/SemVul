try_supercharge(artifact_type *a_ptr, s32b target_power)
{

	if (a_ptr->tval == TV_DIGGING || a_ptr->tval == TV_HAFTED ||
		a_ptr->tval == TV_POLEARM || a_ptr->tval == TV_SWORD)
	{
		if (randint0(z_info->a_max) < artprobs[ART_IDX_MELEE_DICE_SUPER])
		{
			a_ptr->dd += 3 + randint0(4);

			LOG_PRINT1("Supercharging damage dice!  (Now %d dice)\n", a_ptr->dd);
		}
		else if (randint0(z_info->a_max) < artprobs[ART_IDX_MELEE_BLOWS_SUPER])
		{
			of_on(a_ptr->flags, OF_BLOWS);
			a_ptr->pval = 3;
			LOG_PRINT("Supercharging melee blows! (+3 blows)\n");
		}
	}


	if (a_ptr->tval == TV_BOW)
	{
		if (randint0(z_info->a_max) < artprobs[ART_IDX_BOW_SHOTS_SUPER])
		{
			of_on(a_ptr->flags, OF_SHOTS);
			a_ptr->pval = 3;
			LOG_PRINT("Supercharging shots for bow!  (3 extra shots)\n");
		}
		else if (randint0(z_info->a_max) < artprobs[ART_IDX_BOW_MIGHT_SUPER])
		{
			of_on(a_ptr->flags, OF_MIGHT);
			a_ptr->pval = 3;
			LOG_PRINT("Supercharging might for bow!  (3 extra might)\n");
		}
	}


	if (randint0(z_info->a_max) < artprobs[ART_IDX_GEN_SPEED_SUPER] ||
		(a_ptr->tval == TV_BOOTS && randint0(z_info->a_max) <
		artprobs[ART_IDX_BOOT_SPEED]))
	{
		of_on(a_ptr->flags, OF_SPEED);
		a_ptr->pval = 5 + randint0(6);
		if (INHIBIT_WEAK) a_ptr->pval += randint1(3);
		if (INHIBIT_STRONG) a_ptr->pval += 1 + randint1(6);
		LOG_PRINT1("Supercharging speed for this item!  (New speed bonus is %d)\n", a_ptr->pval);
	}


	if (randint0(z_info->a_max) < artprobs[ART_IDX_GEN_AC_SUPER])
	{
		a_ptr->to_a += 19 + randint1(11);
		if (INHIBIT_WEAK) a_ptr->to_a += randint1(10);
		if (INHIBIT_STRONG) a_ptr->to_a += randint1(20);
		LOG_PRINT1("Supercharging AC! New AC bonus is %d\n", a_ptr->to_a);
	}


	if (a_ptr->tval == TV_BOW || a_ptr->tval == TV_DIGGING ||
		a_ptr->tval == TV_HAFTED || a_ptr->tval == TV_POLEARM ||
		a_ptr->tval == TV_SWORD)
	{
		if ((randint0(z_info->a_max) < artprobs[ART_IDX_WEAPON_AGGR]) &&
		    (target_power > AGGR_POWER))
		{
			of_on(a_ptr->flags, OF_AGGRAVATE);
			LOG_PRINT("Adding aggravation\n");
		}
	}
	else
	{
		if ((randint0(z_info->a_max) < artprobs[ART_IDX_NONWEAPON_AGGR]) &&
		    (target_power > AGGR_POWER))
		{
			of_on(a_ptr->flags, OF_AGGRAVATE);
			LOG_PRINT("Adding aggravation\n");
		}
	}
}
