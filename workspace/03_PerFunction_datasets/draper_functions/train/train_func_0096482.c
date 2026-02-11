ai_update_goal_references(ai_goal *goals, int type, const char *old_name, const char *new_name)
{
	int i, mode, flag, dummy;

	for (i=0; i<MAX_AI_GOALS; i++)
	{
		mode = goals[i].ai_mode;
		flag = 0;
		switch (type)
		{
			case REF_TYPE_SHIP:
			case REF_TYPE_PLAYER:
				switch (mode)
				{
					case AI_GOAL_CHASE:
					case AI_GOAL_DOCK:
					case AI_GOAL_DESTROY_SUBSYSTEM:
					case AI_GOAL_GUARD:
					case AI_GOAL_DISABLE_SHIP:
					case AI_GOAL_DISARM_SHIP:
					case AI_GOAL_IGNORE:
					case AI_GOAL_IGNORE_NEW:
					case AI_GOAL_EVADE_SHIP:
					case AI_GOAL_STAY_NEAR_SHIP:
						flag = 1;
				}
				break;

			case REF_TYPE_WING:
				switch (mode)
				{
					case AI_GOAL_CHASE_WING:
					case AI_GOAL_GUARD_WING:
						flag = 1;
				}
				break;

			case REF_TYPE_WAYPOINT:
				switch (mode)
				{
					case AI_GOAL_WAYPOINTS:
					case AI_GOAL_WAYPOINTS_ONCE:
						flag = 1;
				}
				break;

			case REF_TYPE_PATH:
				switch (mode)
				{
					case AI_GOAL_WAYPOINTS:
					case AI_GOAL_WAYPOINTS_ONCE:

						flag = 1;
				}
				break;
		}

		if (flag)
			if (!stricmp(goals[i].target_name, old_name)) {
				if (*new_name == '<')
					goals[i].ai_mode = AI_GOAL_NONE;
				else
					goals[i].target_name = ai_get_goal_target_name(new_name, &dummy);
			}
	}
}
