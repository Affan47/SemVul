gr_opengl_set_team_color(const SCP_string &team, const SCP_string &secondaryteam, fix timestamp, int fadetime) {
	if (secondaryteam == "<none>") {
		if (Team_Colors.find(team) != Team_Colors.end()) {
			Current_team_color = &Team_Colors[team];
			Using_Team_Color = true;
		} else
			Using_Team_Color = false;
	} else {
		if ( Team_Colors.find(secondaryteam) != Team_Colors.end()) {
			team_color temp_color;
			team_color start;
			if (Team_Colors.find(team) != Team_Colors.end()) {
				start = Team_Colors[team];
			} else {
				start.base.r = 0.0f;
				start.base.g = 0.0f;
				start.base.b = 0.0f;

				start.stripe.r = 0.0f;
				start.stripe.g = 0.0f;
				start.stripe.b = 0.0f;
			}
			team_color end = Team_Colors[secondaryteam];
			float time_remaining = (f2fl(Missiontime - timestamp) * 1000)/fadetime;
			CLAMP(time_remaining, 0.0f, 1.0f);
			mix_two_team_colors(&temp_color, &start, &end, time_remaining);

			Current_temp_color = temp_color;
			Current_team_color = &Current_temp_color;
			Using_Team_Color = true;
		} else
			Using_Team_Color = false;
	}
}
