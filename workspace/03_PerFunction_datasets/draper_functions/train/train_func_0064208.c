toggle_fullscreen (void)
{
  Uint32 vid_flags = ne_screen->flags;


  if (GameConfig.UseFullscreen)
    vid_flags &= ~SDL_FULLSCREEN;
  else
    vid_flags |= SDL_FULLSCREEN;

  if( !(ne_screen = SDL_SetVideoMode ( Screen_Rect.w, Screen_Rect.h, 0, vid_flags)) )
    {
      DebugPrintf (0, "ERORR occured when trying ot toggle windowed/fullscreen %d x %d video mode.\n",
		   Screen_Rect.w, Screen_Rect.h);
      DebugPrintf (0, "SDL-Error: %s\n", SDL_GetError() );
      Terminate (ERR);
    }

  if ( ne_screen->flags != vid_flags )
    {
      DebugPrintf (0, "WARNING: Failed to toggle windowed/fullscreen mode!\n");
    }
  else
    GameConfig.UseFullscreen = !GameConfig.UseFullscreen;

  return;
}
