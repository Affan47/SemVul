start ( int x, int y )
{
   if ( scope == 3 ) {

      got = need;
      if ( got > maxint - actmap->bi_resource[player].resource( resourcetype ) )
         got = maxint - actmap->bi_resource[player].resource( resourcetype );

      if ( !queryonly )
         actmap->bi_resource[player].resource( resourcetype ) += got;

   } else
      MapNetwork :: start ( x, y );
}
