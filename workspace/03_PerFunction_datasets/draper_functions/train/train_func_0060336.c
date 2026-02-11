Apply()
{
   for ( int acting = 0; acting < actmap->getPlayerCount(); ++acting )
      for ( int second = 0; second < actmap->getPlayerCount(); ++second ) {

         if ( allEditable ) {
            if ( getState( acting, second ) != actmap->player[acting].diplomacy.getState( second ))
               actmap->player[acting].diplomacy.setState( second, getState( acting, second ));
         } else {
            if ( acting == actmap->actplayer ) {
               if ( stateChanges[acting][second] == SNEAK_ATTACK ) {
                  strategy->sneakAttack( actmap, acting, second );
               } else {
                  DiplomaticStates s = DiplomaticStates( stateChanges[acting][second] - 1);
                  DiplomaticStates t;
                  DiplomaticStateVector::QueuedStateChanges::iterator q = actmap->player[acting].diplomacy.queuedStateChanges.find( second );
                  if ( q == actmap->player[acting].diplomacy.queuedStateChanges.end() )
                     t = getState( acting, second );
                  else
                     t = q->second;

                  if ( t != s ) {
                     strategy->setState( actmap, acting, second, s );
                  }
               }
            }
         }
      }
}
