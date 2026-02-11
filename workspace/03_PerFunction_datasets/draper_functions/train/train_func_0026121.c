DominanceForOne( Bin& bin,
                                   vector<const SizeName*>& unassigned ) const
{
   if( unassigned.empty() ) return 0;

#ifndef RELAXED
   int improved = 0;
   for( int one = 0; one < bin.Count(); ++one )
   {
#else
      int one = Select( 0, bin.Count() - 1 );
#endif
      for( unsigned j = 0; j < unassigned.size(); ++j )
      {
         if( unassigned[j]->Size() > bin[one]->Size() )
         {
            if( unassigned[j]->Size() - bin[one]->Size() <= bin.Free() )
            {
               const SizeName* tmp_item = unassigned[j];


               unassigned.erase( unassigned.begin() + j );


               vector<const SizeName*>::iterator it = lower_bound(
                               unassigned.begin(), unassigned.end(), bin[one],
                               SizeName::CmpSizeRev );

               unassigned.insert( it, bin[one] );

               bin.ReplaceItem( one, tmp_item );

#ifndef RELAXED
               ++improved;
               break;
#else
               return 1;
#endif
            }
         }
         else break;
      }
#ifndef RELAXED
   }
   return improved;
#else
   return 0;
#endif

}
