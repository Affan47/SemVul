process()
{
	if( --delay_remain <= 0)
	{
		cur_frame = rock_res.choose_next(rock_recno, cur_frame, random(ROCK_ALT_PATH) );
		delay_remain = rock_res.get_anim_info(rock_res.get_anim_recno(rock_recno, cur_frame))->delay;
	}
}
