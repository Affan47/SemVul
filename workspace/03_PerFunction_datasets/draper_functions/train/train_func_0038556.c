circularFieldIterator( GameMap* gamemap, const MapCoordinate& center, int startDist, int stopDist, FieldIterationFunctor functor )
{
   SearchFieldsIterator searchFields( gamemap, functor );
   searchFields.initsearch( center, startDist, stopDist );
   searchFields.startsearch();
}
