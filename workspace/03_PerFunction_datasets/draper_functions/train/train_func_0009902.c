movePlayerShot( int dT ) {
  switch (shotType) {
  case SHOT_NORMAL:
  case SHOT_NORMAL_HEAVY:
  case SHOT_DOUBLE:
  case SHOT_DOUBLE_HEAVY:
  case SHOT_TRIPLE:
  case SHOT_HF_NORMAL:
  case SHOT_HF_DOUBLE:
  case SHOT_HF_TRIPLE:
  case SHOT_HF_QUATTRO:
  case SHOT_HF_QUINTO:
  case SHOT_DUMBFIRE:
  case SHOT_DUMBFIRE_DOUBLE:
  case SHOT_KICK_ASS_ROCKET:
  case SHOT_MACHINE_GUN:
  case SHOT_ENERGY_BEAM:
  case SHOT_HF_DUMBFIRE:
  case SHOT_HF_DUMBFIRE_DOUBLE:
  case SHOT_HF_KICK_ASS_ROCKET:
  case SHOT_HF_LASER:
    {
      pos = pos + vel * dT / 1000.0;
      break;
    }
  case SHOT_HELLFIRE:
    {
      pos = pos + vel * dT / 1000.0;
      if ( timeToLive < LIFETIME_SHOT_HELLFIRE - 100 ) {
	vel = Vector2D( 0, -VEL_SHOT_HELLFIRE );
      }
      break;
    }
  case SPECIAL_SHOT_HEATSEEKER:
    {
      pos = pos + vel * dT / 1000.0;
      if ( timeToLive >= LIFETIME_SPECIAL_SHOT_HEATSEEKER - 200 ) break;
      int idxNearestEnemy = 0;
      float distNearest = 10000;
      for ( unsigned int i = 0; i < enemys->getNrEnemys(); i++ ) {

	Vector2D v = enemys->getEnemy(i)->getPos() - pos;
	if ( getAbsAngleDifference( vel.getDirection(), v.getDirection() ) < 180 ) {
	  float dist = (enemys->getEnemy(i)->getPos() - pos).getLength();
	  if ( dist < distNearest ) {
	    distNearest = dist;
	    idxNearestEnemy = i;
	  }
	}
      }
      if ( distNearest != 10000 ) {
	float angle =
	  getAngleDifference( (enemys->getEnemy(idxNearestEnemy)->getPos()-pos).getDirection(),
			      vel.getDirection() );
	if ( fabs(angle) < 80 * dT / 1000.0 ) {
	  vel.rotate(angle);
	} else if ( angle < 0 ) {
	  vel.rotate( -80 * dT / 1000.0 );
	} else {
	  vel.rotate( 80 * dT / 1000.0 );
	}
      }

      break;
    }

  case SPECIAL_SHOT_NUKE:
    {
      pos = pos + vel * dT / 1000.0;

      if ( (pos - Vector2D( SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0 )).getLength()
	   <= (vel * dT / 1000.0).getLength() ) {
	nukeIsInPlace = true;
      }
      break;
    }

  default:
    {
      cout << "movePlayerShot: unexpected shotType: " << shotType << endl;
      break;
    }
  }


  if ( !RectangleGeo( Vector2D( -SHOT_SCREEN_BORDER, -SHOT_SCREEN_BORDER ),
		      Vector2D( SCREEN_WIDTH + SHOT_SCREEN_BORDER,
				SCREEN_HEIGHT + SHOT_SCREEN_BORDER )).isInside(pos) ) {
    timeToLive = 0;
  }
}
