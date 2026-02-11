checkbuilding ( Building* b )
{
   if ( b->color/8 == targplayer ) {
      if ((b->netcontrol & (cnet_stopenergyinput << resourcetype)) == 0) {
         int tostore = need-got;
         if ( b->getStorageCapacity().resource( resourcetype ) - b->actstorage.resource( resourcetype ) < tostore )
            tostore = b->getStorageCapacity().resource( resourcetype ) - b->actstorage.resource( resourcetype );

         if ( !queryonly ) {
            b->actstorage.resource( resourcetype ) += tostore;
            actmap->tribute.avail[ player ][ targplayer ].resource( resourcetype ) -= tostore;
            actmap->tribute.paid [ targplayer ][ player ].resource( resourcetype ) += tostore;
         }
         got += tostore;
      }
   }
}
