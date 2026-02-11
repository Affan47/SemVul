destroyPoolGroup( Index aGroup )
   {


      std::vector<AbstractSemaphorePtr>  dVector;
      Count                         hits(0);

      dVector.clear();

      for( SemaphoreMapIterator aSItr = theSemaphores.begin() ;
          aSItr != theSemaphores.end(); ++aSItr )
      {
         if( (*aSItr).second.theGroupIndex == aGroup )
         {
            ++hits;

            if( (*aSItr).second.theQueueLength == 0 )
            {
               dVector.push_back((*aSItr).first);
            }
            else
            {
               aSItr == theSemaphores.end();
               --aSItr;
            }
         }
         else
         {
            ;
         }
      }


      if( hits == dVector.size() )
      {
         for( Count x = 0; x < hits; ++x )
         {
            theSemaphores.erase( dVector[x] );
            theGroups[aGroup]->destroySemaphore(dVector[x]);
         }
         delete theGroups[aGroup];
         theGroups.pop_back();
      }
      else
      {
         ;
      }

      dVector.clear();
   }
}
