getTransferLimitation( const ContainerBase* target )
{
   if ( target->getOwner() == target->getMap()->actplayer )
      return NONE;

   if ( target->getMap()->player[target->getMap()->actplayer].diplomacy.isAllied( target->getOwner() ))
      return NONE;

   if ( target->getMap()->player[target->getMap()->actplayer].diplomacy.getState( target->getOwner() ) >= PEACE )
      return GET;

   return ALL;
}
