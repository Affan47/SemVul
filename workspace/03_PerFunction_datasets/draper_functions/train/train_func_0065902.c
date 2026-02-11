can_form_new_ai_nation()
{
	return config.new_nation_emerge &&
			 nation_array.ai_nation_count < config.ai_nation_count &&
			 nation_array.nation_count < MAX_NATION &&
			 info.game_date > last_del_nation_date + NEW_NATION_INTERVAL_DAYS &&
			 info.game_date > last_new_nation_date + NEW_NATION_INTERVAL_DAYS;
}
