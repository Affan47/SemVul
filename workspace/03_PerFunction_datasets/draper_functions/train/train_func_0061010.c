CalcWidgetSize( const PG_Point& p, const SDL_Surface* image )
{
   if ( image )
      return PG_Rect (p.x, p.y, image->w, image->h );
   else
      return PG_Rect (p.x, p.y, 1,1 );
}
