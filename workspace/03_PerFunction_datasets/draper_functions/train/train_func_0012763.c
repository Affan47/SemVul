initMovementStructure()
{
   if ( !movementMask[0].mask.valid() )
      for ( int dir = 0; dir < sidenum; ++dir ) {
         movementMask[dir].mask = createMovementBufferSurface();
         MapCoordinate start;
         if ( dir >= 2 && dir <= 4 )
            start = MapCoordinate( 1, 2 );
         else
            start = MapCoordinate( 1, 4 );

         MapCoordinate dest = getNeighbouringFieldCoordinate( start, dir );

         for ( int i = 0; i < sidenum; ++i)
            movementMask[dir].mask.Blit( icons.fieldShape, getFieldPos2( getNeighbouringFieldCoordinate( start, i )));
         for ( int i = 0; i < sidenum; ++i)
            movementMask[dir].mask.Blit( icons.fieldShape, getFieldPos2( getNeighbouringFieldCoordinate( dest, i )));

         SPoint pix = getFieldPos2( start );
         movementMask[dir].startFieldPos = pix;

         pix.x += fieldsizex/2;
         pix.y += fieldsizey/2;
         movementMask[dir].mask.SetColorKey( SDL_SRCCOLORKEY, movementMask[dir].mask.GetPixel( pix ) & ~movementMask[dir].mask.GetPixelFormat().Amask());
      }
}
