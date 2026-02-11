drawRacer( SDL_Surface *screen ) {

  SDL_Rect srcR;
  SDL_Rect destR;

  destR.x = lroundf(pos.getX()) - (spriteRacerBase->w / (2*RACER_IMAGE_CNT));
  destR.y = lroundf(pos.getY()) - (spriteRacerBase->h / 2);
  destR.w = spriteRacerBase->w / RACER_IMAGE_CNT;
  destR.h = spriteRacerBase->h;

  int idx = 0;
  if ( !left && !right && !thrust && !backwards ) idx = 0;
  else if ( left && !right && !thrust && !backwards ) idx = 1;
  else if ( !left && right && !thrust && !backwards ) idx = 2;
  else if ( !left && !right && thrust && !backwards ) idx = 3;
  else if ( !left && !right && !thrust && backwards ) idx = 4;
  else if ( left && !right && thrust && !backwards ) idx = 5;
  else if ( !left && right && thrust && !backwards ) idx = 6;
  else if ( left && !right && !thrust && backwards ) idx = 7;
  else if ( !left && right && !thrust && backwards ) idx = 8;
  srcR.x = idx * (spriteRacerBase->w / RACER_IMAGE_CNT);
  srcR.y = 0;
  srcR.w = (spriteRacerBase->w / RACER_IMAGE_CNT);
  srcR.h = spriteRacerBase->h;

  SDL_BlitSurface( spriteRacerBase, &srcR, screen, &destR );

  if ( shieldDamageActive ) {
    int shieldGlowTimeLeft = shieldDamageEndTime - SDL_GetTicks();
    if ( shieldGlowTimeLeft < 0 ) {
      shieldDamageActive = false;
    } else {
      shieldGlow->draw( screen, pos, RACER_SHIELD_DAMAGE_LIFETIME - shieldGlowTimeLeft );
    }
  }

  if ( deflectorActive ) {
    drawRectDeflector.x = lroundf(pos.getX()) - spriteDeflector->w / 2;
    drawRectDeflector.y = lroundf(pos.getY()) - spriteDeflector->h / 2;
    SDL_BlitSurface( spriteDeflector, 0, screen, &drawRectDeflector );
  }
}
