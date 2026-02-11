off()
{
	_enemy *enemyp;
	for(enemyp = enemy; enemyp < enemy + ENEMY_MAX; enemyp++)
		enemyp->release();
}
