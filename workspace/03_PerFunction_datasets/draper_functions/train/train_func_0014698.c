emptyDest()
{
   for ( Transfers::iterator i = transfers.begin(); i != transfers.end(); ++i )
      (*i)->empty( dest );

}
