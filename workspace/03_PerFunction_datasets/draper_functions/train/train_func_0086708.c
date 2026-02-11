QuitGameMenu (void)
{
  InitiateMenu (TRUE);

  PutString (ne_screen, User_Rect.x + User_Rect.w/10,
	      User_Rect.y + User_Rect.h/2, "Do you really want to quit? (y/n) ");
  SDL_Flip (ne_screen);

  while ( (!KeyIsPressed('n')) && (!KeyIsPressed('y')) ) SDL_Delay(1);
  if (KeyIsPressed('y'))
    Terminate (OK);
}
