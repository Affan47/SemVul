BlitScreen(uint8 *XBuf)
{
 SDL_Surface *TmpScreen;
 uint8 *dest;
 int xo=0,yo=0;

 if(!screen) return;

 if(paletterefresh)
 {
  RedoPalette();
  paletterefresh=0;
 }

 #ifdef OPENGL
 if(usingogl)
 {
  BlitOpenGL(XBuf);
  return;
 }
 #endif

 XBuf+=srendline*256;

 if(BlitBuf) TmpScreen=BlitBuf;
 else TmpScreen=screen;

 if(SDL_MUSTLOCK(TmpScreen))
  if(SDL_LockSurface(TmpScreen))
  {
   return;
  }

 dest=(uint8*)TmpScreen->pixels;

 if(_fullscreen)
 {
  xo=(((TmpScreen->w-NWIDTH*exs))/2);
  dest+=xo*(curbpp>>3);
  if(TmpScreen->h>(tlines*eys))
  {
   yo=((TmpScreen->h-tlines*eys)/2);
   dest+=yo*TmpScreen->pitch;
  }
 }

 if(curbpp>8)
 {
  if(BlitBuf)
   Blit8ToHigh(XBuf+NOFFSET,dest, NWIDTH, tlines, TmpScreen->pitch,1,1);
  else
   Blit8ToHigh(XBuf+NOFFSET,dest, NWIDTH, tlines, TmpScreen->pitch,exs,eys);
 }
 else
 {
  if(BlitBuf)
   Blit8To8(XBuf+NOFFSET,dest, NWIDTH, tlines, TmpScreen->pitch,1,1,0,sponge);
  else
   Blit8To8(XBuf+NOFFSET,dest, NWIDTH, tlines, TmpScreen->pitch,exs,eys,eefx,sponge);
 }
 if(SDL_MUSTLOCK(TmpScreen))
  SDL_UnlockSurface(TmpScreen);

 if(BlitBuf)
 {
  SDL_Rect srect;
  SDL_Rect drect;

  srect.x=0;
  srect.y=0;
  srect.w=NWIDTH;
  srect.h=tlines;

  drect.x=0;
  drect.y=0;
  drect.w=exs*NWIDTH;
  drect.h=eys*tlines;

  SDL_BlitSurface(BlitBuf, &srect,screen,&drect);
 }

 SDL_UpdateRect(screen, xo, yo, NWIDTH*exs, tlines*eys);

 if(screen->flags&SDL_DOUBLEBUF)
  SDL_Flip(screen);
}
