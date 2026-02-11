setup( PG_Widget* parent, ContainerBase* container, HighLightingManager& highLightingManager, int& unitColumnCount )
{
   vector<StoringPosition*> storingPositionVector;
   if ( parent) {
      int x = 0;
      int y = 0;
      int posNum = container->baseType->maxLoadableUnits;
      if ( container->getCargo().size() > posNum )
         posNum = container->getCargo().size();

      for ( int i = 0; i < posNum; ++i ) {
         StoringPosition* sp = new StoringPosition( parent, PG_Point( x, y), PG_Point(-1,-1), highLightingManager, container->getCargo(), i, container->baseType->maxLoadableUnits >= container->getCargo().size() );
         storingPositionVector.push_back( sp );
         x += StoringPosition::spWidth;
         if ( x + StoringPosition::spWidth >= parent->Width() - 20 ) {
            if ( !unitColumnCount )
               unitColumnCount = i + 1;
            x = 0;
            y += StoringPosition::spHeight;
         }
      }
   }
   return storingPositionVector;
}
