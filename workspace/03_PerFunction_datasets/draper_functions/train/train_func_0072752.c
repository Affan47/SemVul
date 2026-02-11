add_bullet(Unit* parentUnit, Unit* targetUnit)
{


	SpriteInfo *targetSpriteInfo = targetUnit->sprite_info;
	AttackInfo *attackInfo = parentUnit->attack_info_array+parentUnit->cur_attack;
	short attackXLoc	= parentUnit->range_attack_x_loc;
	short attackYLoc	= parentUnit->range_attack_y_loc;
	short targetXLoc = targetUnit->next_x_loc();
	short targetYLoc = targetUnit->next_y_loc();

	if(attackXLoc >= targetXLoc && attackXLoc < targetXLoc+targetSpriteInfo->loc_width &&
		attackYLoc >= targetYLoc && attackYLoc < targetYLoc+targetSpriteInfo->loc_height)
	{


		short bulletId = (parentUnit->attack_info_array+parentUnit->cur_attack)->bullet_sprite_id;
		Bullet* bulletPtr;
		create_bullet( bulletId, &bulletPtr);
		bulletPtr->init(BULLET_BY_UNIT, parentUnit->sprite_recno, attackXLoc, attackYLoc, targetUnit->mobile_type);
		err_when(parentUnit->cur_dir!=parentUnit->final_dir);

		return 1;
	}

	err_here();
	return 0;
}
