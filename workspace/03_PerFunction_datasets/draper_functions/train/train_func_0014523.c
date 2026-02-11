setupCommonAccess
      (
         CharCptr aName,
         const CreateDisposition &aMode
      )
   {
      REQUIRE( aName != NULLPTR );

      struct   stat     statRet;
               Int      results(0);
               int      errRet(0);

      int   stret = stat(aName,&statRet);


      if( stret == -1 )
      {
         errRet = Int(*__errno_location());


         if( errRet == ENOENT )
         {
            if( aMode == FAIL_IF_NOTEXISTS )
            {
               results = -1;
            }
            else
            {
               results = 1;

               Int fhndl = open
               (
                  aName,
                  O_CREAT | O_EXCL,
                  OWNER_ALL | GROUP_ALL | PUBLIC_ALL
               );

               if( fhndl != -1 )
               {
                  close(fhndl);
               }
               else
               {
                  results = fhndl;
               }
            }
         }


         else
         {
            results = -1;
         }
      }


      else
      {
         if( aMode == FAIL_IF_EXISTS )
         {
            results = -1;
         }
         else
         {
            ;
         }
      }

      return results;
   }
