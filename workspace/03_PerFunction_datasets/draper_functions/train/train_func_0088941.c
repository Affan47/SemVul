getlocap(lofig_list *ptfig, const char *cname)
{
  locap_list *ptcap = NULL ;
  char       *name  = namealloc(cname) ;

  for(ptcap = ptfig -> LOCAP ; ptcap != NULL ; ptcap = ptcap -> NEXT)
    {
      if(ptcap -> NAME == name)
	{
          return ptcap ;
	}
    }

  (void)fflush(stdout) ;
  (void)fprintf(stderr,"*** mbk error ***\n") ;
  (void)fprintf(stderr,"getlocap impossible :\n") ;
  (void)fprintf(stderr,"capacitor %s doesn't exist in figure %s\n",name,ptfig -> NAME) ;
  EXIT(1) ;

  return NULL ;
}
