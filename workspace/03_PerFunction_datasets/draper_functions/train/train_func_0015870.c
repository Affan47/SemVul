select_prev(int redraw_map)
{
	scene_num--;
	if(scene_num < 0)
	{
		sound.ui_error();
		scene_num = 0;
	}
	else
		sound.ui_tick();
	select_scene(scene_num);
}
