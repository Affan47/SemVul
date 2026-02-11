hit( ParticleInfo *p, int damage, int )
{

    static ParticleGroup *effects =
	ParticleGroupManagerS::instance()->getParticleGroup( EFFECTS_GROUP2);

    _energy -= damage;
    if( _energy <= 0)
    {
	static ParticleGroup *bonus =
	    ParticleGroupManagerS::instance()->getParticleGroup( BONUS_GROUP);

	p->tod = 0;
	if( _moveState == eAttack)
	{
	    ScoreKeeperS::instance()->addToCurrentScore( 200);
	}
	else
	{
	    ScoreKeeperS::instance()->addToCurrentScore( 100);
	}

	if( (Random::random() & 0xff) > 10)
	    bonus->newParticle( "Bonus1",
		p->position.x, p->position.y, p->position.z);
	else
	    bonus->newParticle( "SuperBonus",
		p->position.x, p->position.y, p->position.z);


	for( int i=0; i<(int)(GameState::horsePower/2.0); i++)
	{
	    effects->newParticle(
		"ExplosionPiece", p->position.x, p->position.y, p->position.z);
	}
	AudioS::instance()->playSample( "sounds/explosion.wav");
    }
    else
    {

	ScoreKeeperS::instance()->addToCurrentScore( 50);

	ParticleInfo pi;

	pi.position.x = p->position.x;
	pi.position.y = p->position.y;
	pi.position.z = p->position.z;

	pi.velocity.x = _dir.x*0.6f*GAME_STEP_SCALE;
	pi.velocity.y = _dir.y*0.6f*GAME_STEP_SCALE;
	pi.velocity.z = _dir.z*0.6f*GAME_STEP_SCALE;

	effects->newParticle( "MiniSmoke", pi);
    }
}
