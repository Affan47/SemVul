removeCommonAccess( CharCptr aName )
   {
      REQUIRE( aName != NULLPTR );

      struct   stat     statRet;
               Int      stret( stat(aName,&statRet) );

      if( stret != -1 )
      {
         stret = unlink(aName);
      }
      else
      {
         ;
      }

      return stret;
   }
