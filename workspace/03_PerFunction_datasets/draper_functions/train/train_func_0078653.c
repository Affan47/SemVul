init()
{
	_enemy *enemyp;
	for(enemyp = enemy; enemyp < enemy + ENEMY_MAX; enemyp++)
		enemyp->init();
	enemy_max = enemy;
	ekind_to_generate_1 = NULL;
	ekind_to_generate_2 = NULL;
	e1_interval = 1;
	e2_interval = 1;
	return 0;
}
