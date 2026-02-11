move_cannon()
{
	(count)++;
	(count) &= (b);
	if(count == a && norm < ((VIEWLIMIT >> 1) + 8))
	{
		int shift = (enemies.ek1() == &beam) ? 6 : 5;
		this->shot_template(enemies.ek1(), shift, 32, 0);
	}
}
