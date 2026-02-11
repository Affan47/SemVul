one_time_brain(int h)
{


	if (spr[h].move_active)
	{
		process_move(h);
		return;
	}

	if (spr[h].follow > 0)
	{
		process_follow(h);
	}


	if (spr[h].seq == 0)
	{
	  draw_sprite_game(GFX_lpDDSTwo, h);
		spr[h].active = 0;
		return;
	}

	changedir(spr[h].dir,h,-1);
	automove(h);

}
