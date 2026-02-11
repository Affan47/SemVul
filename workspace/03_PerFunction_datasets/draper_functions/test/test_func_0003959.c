kill_enemy(enemy * target, char givexp, int killertype)
{
	int reward = 0;


	if (givexp) {
		reward = Druidmap[target->type].experience_reward * Me.experience_factor;
		Me.Experience += reward;
	}

	if (is_friendly(target->faction, FACTION_SELF)) {
		if (killertype > -1) {
			enemy *killer = NULL;
			killer = enemy_resolve_address(killertype, &killer);
			append_new_game_message(_("Your friend \4%s\5 was killed by %s."),
			target->short_description_text, killer->short_description_text);
		} else if ((killertype == -1) && (givexp)) {
                        append_new_game_message(_("You killed \4%s\5."), target->short_description_text);
			Me.destroyed_bots[target->type]++;
		} else if (killertype == -2) {
                        append_new_game_message(_("\4%s\5 halted and caught fire."), target->short_description_text);
		} else {
                        append_new_game_message(_("\4%s\5 is dead."), target->short_description_text);
		}
	} else {
		if (givexp && (killertype == -1)) {
			append_new_game_message(_("For defeating \4%s\5, you receive %d experience."), target->short_description_text,
						reward);
			Me.destroyed_bots[target->type]++;
		}


	}

	if (MakeSureEnemyIsInsideHisLevel(target)) {

		DropEnemyTreasure(target);


		target->animation_phase = ((float)first_death_animation_image[Druidmap[target->type].individual_shape_nr]) - 1 + 0.1;
		target->animation_type = DEATH_ANIMATION;
		play_death_sound_for_bot(target);
		DebugPrintf(1, "\n%s(): playing death sound because bot of type %d really died.", __FUNCTION__, Druidmap[target->type].individual_shape_nr);

		if (MyRandom(15) == 1)
			enemy_spray_blood(target);
	}

	list_move(&(target->global_list), &dead_bots_head);
	list_del(&(target->level_list));

	event_enemy_died(target);

	return 0;
}
