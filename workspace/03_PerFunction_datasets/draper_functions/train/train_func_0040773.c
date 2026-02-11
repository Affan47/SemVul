update()
{
	float	v[3] = { 0.0, -0.2, 0.0 };

	float	*hpos = game->hero->getPos();
	float	a = hpos[0]-pos[0];
	float	b = hpos[1]-pos[1];


	age++;
	shootInterval--;

	pos[0] += secondaryMove[0]*game->speedAdj;
	pos[1] += secondaryMove[1]*game->speedAdj;
	float s = (1.0-game->speedAdj)+(game->speedAdj*0.7);
	secondaryMove[0] *= s;
	secondaryMove[1] *= s;
	move();

	float	p[3] = { pos[0], pos[1], pos[2] };

	if(!shootInterval)
	{
		calcShootInterval();
		if(fabs(a) < 2.0 && b < 0.0)
		{
			v[1] = -0.39;
			p[1] = pos[1]-0.5;
			game->enemyAmmo->addAmmo(4, p, v);
		}
	}
}
