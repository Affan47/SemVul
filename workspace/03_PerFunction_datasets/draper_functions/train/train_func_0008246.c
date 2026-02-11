attack_wall(int damage)
{
	err_when( !is_wall() );

	if(damage >= WALL_DEFENCE + MIN_WALL_DAMAGE)
		damage -= WALL_DEFENCE;
	else if( damage >= MIN_WALL_DAMAGE )
		damage = MIN_WALL_DAMAGE;
	else if( damage <= 0)
		return wall_hit_point();

	int hp = wall_hit_point();
	if( hp > 0)
	{
		hp-= damage;
		if( hp <= 0)
		{
			hp = 0;
			remove_wall();
			return 0;
		}
	}
	else if( hp < 0)
	{
		hp+= damage;
		if( hp >= 0)
		{
			hp = 0;
			remove_wall();
			return 0;
		}
	}
	cargo_recno = (hp << 8) | wall_town_recno();
	return hp;
}
