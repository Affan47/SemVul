do_random_sidethrust(ai_info *aip, ship_info *sip)
{

	vec2d side_vec;

	int strafeHoldDirAmount = (int)(sip->slide_accel) + static_rand_range((Missiontime + static_rand(aip->shipnum)) >> 18, 1, 3);


	if (strafeHoldDirAmount > 0) {
		side_vec.x = static_randf_range((((Missiontime + static_rand(aip->shipnum)) >> 16) / strafeHoldDirAmount) , -1.0f, 1.0f);
		side_vec.y = static_randf_range((((Missiontime + static_rand(aip->shipnum)) >> 16) / strafeHoldDirAmount) * 2, -1.0f, 1.0f);
	} else {
		Warning(LOCATION, "Division by zero in do_random_sidethrust averted. Please tell a coder.\n");
		side_vec.x = 1.0f;
		side_vec.y = 1.0f;
	}

	vm_vec_boxscale(&side_vec, 1.0f);

	AI_ci.sideways = side_vec.x;
	AI_ci.vertical = side_vec.y;
}
