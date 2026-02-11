Ai_goal_text(int goal)
{
	switch(goal)	{
	case 1:
		return XSTR( "attack ", 474);
	case 2:
		return XSTR( "dock ", 475);
	case 3:
		return XSTR( "waypoints", 476);
	case 4:
		return XSTR( "waypoints", 476);
	case 6:
		return XSTR( "destroy ", 477);
	case 7:
		return XSTR( "form on ", 478);
	case 8:
		return XSTR( "undock ", 479);
	case 9:
		return XSTR( "attack ", 474);
	case 10:
		return XSTR( "guard ", 480);
	case 11:
		return XSTR( "disable ", 481);
	case 12:
		return XSTR( "disarm ", 482);
	case 15:
		return XSTR( "guard ", 480);
	case 16:
		return XSTR( "evade ", 483);
	case 19:
		return XSTR( "rearm ", 484);
	}


	return NULL;
}
