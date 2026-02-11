setTargetPosition( const MapCoordinate& pos )
{
   this->target = pos;
   MapField* fld = getMap()->getField(target);

   if ( !fld )
      throw ActionResult(21002);

   setState( SetUp );

}
