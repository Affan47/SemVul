open()
{
	if(init_display(prefs) < 0)
		return -1;

#ifdef TIME_PROGRESS
	wdash->progress_init(NULL);
#else
	wdash->progress_init(progtab_all);
#endif

	if(load_graphics(prefs) < 0)
		return -2;

#ifdef TIME_PROGRESS

	wdash->progress_done();
	wdash->progress_init(NULL);
#endif

	sound.open();

	if(load_sounds(prefs) < 0)
		return -3;

	wdash->progress_done();

	wdash->nibble();

	ct_engine.render_highlight = kobo_render_highlight;
	wdash->mode(DASHBOARD_GAME);
	wradar->mode(RM_NOISE);
	pubrand.init();
	init_js(prefs);
	gamecontrol.init(prefs->always_fire);
	manage.init();

	gsm.push(&st_intro_title);

	return 0;
}
