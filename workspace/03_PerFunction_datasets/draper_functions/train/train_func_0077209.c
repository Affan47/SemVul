display( SDL_Surface * surface, const PG_Rect & src, const PG_Rect & dst )
{
   if ( !getClippingSurface().valid() )
      getClippingSurface() = Surface::createSurface( fieldsizex + 10, fieldsizey + 10, 32, 0 );

   getClippingSurface().Fill(0);

   vt->paint( getClippingSurface(), SPoint(5,5), player.getPlayerColor(), 0 );
   PG_Draw::BlitSurface( getClippingSurface().getBaseSurface(), PG_Rect( src.x + 5, src.y + 5, src.w, src.h), surface, dst);
}
