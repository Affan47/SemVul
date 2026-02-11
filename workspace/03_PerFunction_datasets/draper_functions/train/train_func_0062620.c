stars_draw(int show_stars, int show_suns, int show_nebulas, int show_subspace, int env)
{
	int gr_zbuffering_save = gr_zbuffer_get();
	gr_zbuffer_set(GR_ZBUFF_NONE);

	Rendering_to_env = env;

	if (show_subspace)
		subspace_render();

	if (Num_stars >= MAX_STARS)
		Num_stars = MAX_STARS;

#ifdef TIME_STAR_CODE
	fix xt1, xt2;
	xt1 = timer_get_fixed_seconds();
#endif

	if ( show_nebulas && (Game_detail_flags & DETAIL_FLAG_NEBULAS) && (Neb2_render_mode != NEB2_RENDER_POF) && (Neb2_render_mode != NEB2_RENDER_LAME))	{
		nebula_render();
	}


	if ( (Neb2_render_mode != NEB2_RENDER_POLY) && (Neb2_render_mode != NEB2_RENDER_LAME) && show_stars ) {

		int neb_save = Neb2_render_mode;
		Neb2_render_mode = NEB2_RENDER_NONE;
		stars_draw_background();
		Neb2_render_mode = neb_save;
	}
	else if ( !show_subspace )
	{
		stars_draw_background();
	}

	if ( !env && show_stars && (Nmodel_num < 0) && (Game_detail_flags & DETAIL_FLAG_STARS) && !(The_mission.flags & MISSION_FLAG_FULLNEB) && (supernova_active() < 3) ) {
		stars_draw_stars();
	}

	last_stars_filled = 1;

#ifdef TIME_STAR_CODE
	xt2 = timer_get_fixed_seconds();
	mprintf(( "Stars: %d\n", xt2-xt1 ));
#endif

	if ( !Rendering_to_env && (Game_detail_flags & DETAIL_FLAG_MOTION) && (!Fred_running) && (supernova_active() < 3) && (!Cmdline_nomotiondebris) )	{
		stars_draw_debris();
	}


	if (show_suns) {
		stars_draw_sun( show_suns );
		stars_draw_bitmaps( show_suns );
	}

	gr_zbuffer_set( gr_zbuffering_save );
	Rendering_to_env = 0;
}
