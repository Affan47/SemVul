addExplosion() {
  Explosion *explosion;
  switch (shotType) {
  default:
    {
      if ( collidedWithGround ) {
	explosion = new Explosion( FN_EXPLOSION_NORMAL, pos,
				   vel / 10.0, EXPLOSION_NORMAL_GROUND );
      } else {
	if ( shotType == SHOT_HF_LASER ) {

	  explosion = new Explosion( FN_EXPLOSION_NORMAL, pos,
				     vel / 30.0, EXPLOSION_NORMAL_AIR );
	} else {
	  explosion = new Explosion( FN_EXPLOSION_NORMAL, pos,
				     vel / 10.0, EXPLOSION_NORMAL_AIR );
	}
      }
      break;
    }
  }
  explosions->addExplosion( explosion );
}
