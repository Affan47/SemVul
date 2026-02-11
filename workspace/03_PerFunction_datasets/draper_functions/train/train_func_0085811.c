copy2screen( int x1, int y1, int x2, int y2 )
{
   MouseHider mouseHider;

   if ( !dummyScreenPaletteSetup ) {
      hgmp->surface->assignDefaultPalette();
      dummyScreenPaletteSetup = true;
   }

   if ( screen->format->BitsPerPixel > 8 ) {
      SDL_Rect r;
      r.x = min(x1,x2);
      r.y = min(y1,y2);
      r.w = abs(x2-x1)+1;
      r.h = abs(y2-y1)+1;

      SDL_BlitSurface( hgmp->surface->getBaseSurface() , &r, screen, &r );
   }

   if ( x1 == -1 || y1 == -1 || x2 == -1 || y2 == -1 )
      SDL_UpdateRect ( screen , 0,0,0,0 );
   else
      if ( x1 <= x2 && y1 <= y2 )
         SDL_UpdateRect ( screen , x1, y1, x2-x1+1, y2-y1+1 );
      else
         if( x1 > x2 )
            SDL_UpdateRect ( screen , x2, y1, x1-x2+1, y2-y1+1 );
         else
            SDL_UpdateRect ( screen , x1, y2, x2-x1+1, y1-y2+1 );

   return 0;
}
