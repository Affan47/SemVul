set_nth_quick_skill(int quick_skill)
{
		int ski =
		    CursorIsOnWhichSkillButton(GetMousePos_x(),
					       GetMousePos_y()) +
		    NUMBER_OF_SKILLS_PER_SKILL_PAGE * GameConfig.spell_level_visible;


		int SkillSubsetMap[number_of_skills];
		establish_skill_subset_map(&(SkillSubsetMap[0]));
		ski = SkillSubsetMap[ski];

		if (Me.skill_level[ski] <=  0) {

			ErrorMessage(__FUNCTION__,
				"Tried to set skill number %d in quick skills. Skill was not acquired yet.\n",
					PLEASE_INFORM, IS_WARNING_ONLY, ski);
			return;
		}
		int i;

		for (i = 0; i < 10; i++) {
			if (Me.program_shortcuts[i] == ski && i != quick_skill)
				Me.program_shortcuts[i] = -1;
		}

		Me.program_shortcuts[quick_skill] = ski;
}
