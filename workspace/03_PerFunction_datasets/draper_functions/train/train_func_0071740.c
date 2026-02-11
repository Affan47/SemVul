move_enemy2()
{
	this->move_enemy_template(4, 192);
	if(--(count) <= 0)
	{
		if(norm < ((VIEWLIMIT >> 1) + 8))
		{
			this->shot_template(&beam, 5, 0, 0);
		}
		count = 32;
	}
}
