TakeScreenshot(void)
{
  static int Number_Of_Screenshot=0;
  char Screenshoot_Filename[100];

  Activate_Conservative_Frame_Computation();

  sprintf( Screenshoot_Filename , "Screenshot_%d.bmp", Number_Of_Screenshot );
  SDL_SaveBMP( ne_screen , Screenshoot_Filename );
  Number_Of_Screenshot++;
  DisplayBanner ("Screenshot", NULL,  BANNER_NO_SDL_UPDATE | BANNER_FORCE_UPDATE );
  MakeGridOnScreen(NULL);
  SDL_Flip (ne_screen);
  Play_Sound (SCREENSHOT_SOUND);

  while (cmd_is_active(CMD_SCREENSHOT)) SDL_Delay(1);

  DisplayBanner (NULL, NULL, BANNER_FORCE_UPDATE );

  return;

}
