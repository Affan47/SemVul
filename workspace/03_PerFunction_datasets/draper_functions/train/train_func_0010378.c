player_controls_init()
{
	static int initted = 0;

	if (initted)
		return;

	initted = 1;
	physics_init( &Descent_physics );
	Descent_physics.flags |= PF_ACCELERATES | PF_SLIDE_ENABLED;

	Viewer_slew_angles_delta.p = 0.0f;
	Viewer_slew_angles_delta.b = 0.0f;
	Viewer_slew_angles_delta.h = 0.0f;
}
