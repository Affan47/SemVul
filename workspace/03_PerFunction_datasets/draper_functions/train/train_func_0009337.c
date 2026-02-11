markField2( const MapCoordinate& pos, const SPoint& mouse, bool cursorChanged, int button, int prio )
{
   if ( prio <= 2 )
      markField( pos );
   return true;
}
