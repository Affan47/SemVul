ShowDeckMap (Level deck)
{
  finepoint tmp;
  tmp.x=Me.pos.x;
  tmp.y=Me.pos.y;

  Me.pos.x = CurLevel->xlen/2;
  Me.pos.y = CurLevel->ylen/2;

  SDL_ShowCursor (SDL_DISABLE);

  SetCombatScaleTo( 0.25 );

  Assemble_Combat_Picture( ONLY_SHOW_MAP|SHOW_FULL_MAP );

  SDL_Flip (ne_screen);

  Me.pos.x=tmp.x;
  Me.pos.y=tmp.y;

  while (! (FirePressedR() || EscapePressedR() || MouseRightPressedR() ))
    SDL_Delay(1);

  SetCombatScaleTo (1.0);

  return;
}
