main(int argc, char *argv[])
{
   char * dirtosearch=0;
   struct AISLib_SearchCriteria * criteria=AISLib_createCriteria();
   if ( argc <1 )        { fprintf(stderr,"Argument zero should be executable path :S \n"); return 1; } else
    { dirtosearch = AISLib_loadDirAndCriteriaFromArgs(argc,argv,criteria); }

   if (criteria->needHelp)
    {
        displayHelp();
        return 0;
    }

   struct AISLib_SearchResults *  result =  AISLib_Search(dirtosearch,criteria);

   AISLib_destroySearchResults(result);
   AISLib_destroyCriteria(criteria);
   if (dirtosearch!=0) { free(dirtosearch); }
   return 0;
}
