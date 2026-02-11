setJob ( Job j )
{
   int pos = 0;
   for ( JobList::iterator i = jobs.begin(); i != jobs.end(); ++i, ++pos )
      if ( *i == j ) {
         jobPos = pos;
         return;
      }

   addJob ( j, true );
}
