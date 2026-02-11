mission_diary_add(const char *mis_name, const char *diarytext)
{
	int mis_num = GetMissionIndexByName(mis_name);
	int idx = 0;

	while (Me.AllMissions[mis_num].mission_diary_texts[idx] && idx < MAX_MISSION_DESCRIPTION_TEXTS)
		idx++;

	if (idx >= MAX_MISSION_DESCRIPTION_TEXTS) {
		ErrorMessage(__FUNCTION__,
			     "There is no more room to append mission diary text \"%s\" to mission name \"%s\". Doing nothing.\n",
			     PLEASE_INFORM, IS_WARNING_ONLY, diarytext, mis_name);
		return;
	}

	Mission_Status_Change_Sound();

	Me.AllMissions[mis_num].mission_description_time[idx] = Me.current_game_date;

	Me.AllMissions[mis_num].mission_diary_texts[idx] = strdup(diarytext);

	Me.quest_browser_changed = 1;
}
