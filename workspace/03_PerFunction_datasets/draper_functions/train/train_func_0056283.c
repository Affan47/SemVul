readProcess()
{
   process_t **pp_p ;
   char dlim[5] ;

   plist_cnt = 0;
   process_list = NULL ;
   pp_p = &process_list ;
   while (fgets(dlim, sizeof(dlim), fp) != NULL)
    {
       if (!strcmp(dlim, BO_HAND))
	{
	   *pp_p = NULL ;
	   return ;
	}
       if (strcmp(dlim, BO_PROC))
	{
	  if (!strcmp(dlim,"debu"))
	  {
		r_debug = 1;
		if (fgets(dlim, sizeof(dlim), fp) == NULL)
			exit(E_EOF);
		if (fgets(dlim, sizeof(dlim), fp) == NULL)
			exit(E_EOF);
		if (!strcmp(dlim, BO_HAND))
		{
			*pp_p = NULL;
			return;
		}
	  }
	  else exit(E_DELIMITER) ;
	}

       if ((*pp_p = (process_t *) malloc(sizeof(process_t))) == NULL)
	  exit(E_MALLOC) ;
       if (fscanf(fp, "%s", (*pp_p)->name) != 1)
	  exit(E_PROCNAME) ;

       readLocation(*pp_p) ;
       readParams(*pp_p) ;
       readArgs(*pp_p) ;
       readLinks(*pp_p) ;
       plist_cnt ++;
       pp_p = &(*pp_p)->next ;
    }
   exit(E_EOF) ;
}
