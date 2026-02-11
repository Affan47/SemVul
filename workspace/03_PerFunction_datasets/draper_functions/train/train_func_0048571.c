render(float frametime)
{
	object* targetp;

	if (Player_ai->target_objnum == -1 || Player->target_is_dying)
		return;

	targetp = &Objects[Player_ai->target_objnum];

	if ( maybeFlashSexp() == 1 ) {
		hud_set_iff_color( targetp );
	} else {
		hud_set_iff_color( targetp, 1);
	}
	renderOrientation(targetp, Player_obj, &targetp->orient);
}
