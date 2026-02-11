next_scene()
{
#ifdef PLAYSTATS
	printf("stage %d:\n", scene_num);
	Uint32 nst = SDL_GetTicks();
	printf("    time:   %d s\n", (nst - start_time) / 1000);
	printf("  deaths:   %d\n", start_ships - ships);
	start_time = nst;
	start_ships = ships;
#endif
	scene_num++;
	if(scene_num >= GIGA - 1)
		scene_num = GIGA - 2;
	screen.init_scene(scene_num);
	scroll_jump = 1;
	_get_ready = 1;
}
