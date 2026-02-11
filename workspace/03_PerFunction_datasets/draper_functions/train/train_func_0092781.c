hud_stuff_reticle_list(reticle_list *rl, object *objp, float measure, int dot_flag)
{
	if ( dot_flag ) {
		rl->dot = measure;
		rl->dist = RETICLE_DEFAULT_DIST;
		rl->flags |= RL_USE_DOT;
	}
	else {
		rl->dist = measure;
		rl->dot = RETICLE_DEFAULT_DOT;
	}
	rl->objp = objp;
}
