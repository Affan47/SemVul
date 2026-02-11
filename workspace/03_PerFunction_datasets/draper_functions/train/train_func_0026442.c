UpdateHex( const Point &hex ) {
  if ( !Enabled() ) return Rect(0,0,0,0);

  Point p = Hex2Pixel( hex );

  Rect clip( p.x, p.y, TileWidth(), TileHeight() );
  clip.Clip( *this );


  DrawTerrain( map->HexImage( hex ), surface, p.x, p.y, clip );


  if ( Unit *u = map->GetUnit( hex ) ) {
    DrawUnit( u->Image(), surface, p.x, p.y, clip );
    if ( !u->IsReady() ) DrawTerrain( IMG_NOT_AVAILABLE, surface, p.x, p.y, clip );


    if ( UnitStatsEnabled() )
      DrawUnitHealth( u->GroupSize(), surface, p.x, p.y, clip );
  }


  if ( FogEnabled() && (shader_map[map->Hex2Index(hex)] == -1) )
    DrawFog( surface, p.x, p.y, clip );


  if ( CursorEnabled() && (hex == cursor) )
    DrawTerrain( cursor_image, surface, p.x, p.y, clip );

  return clip;
}
