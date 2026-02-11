sortchain(entree,champ)
chain_list	*entree;
char		 champ;
{
  chain_list	*scanchain,*sortie,*last,*prevmax,*eff;
  znc		*maxi,*z;


  if(!entree)
  {
    fprintf(stderr,"Trie de chaine (null). \n");
    exit(-1);
  }

  if(entree->NEXT==NULL)
    return(entree);

  sortie=NULL;

  while(entree)
  {

    maxi=(znc*)entree->DATA;


    last=NULL;
    prevmax=NULL;

    for(scanchain=entree;scanchain;scanchain=scanchain->NEXT)
    {
      z=(znc*)(scanchain->DATA);

      if( ( champ=='X' && z->x1 > maxi->x1 ) ||
          ( champ=='Y' && z->y1 > maxi->y1 )    )
      {
        maxi = z;
        prevmax=last;
      }
      last=scanchain;
    }


    sortie=addchain(sortie,maxi);


    if(prevmax)
    {
      eff=prevmax->NEXT;
      prevmax->NEXT=prevmax->NEXT->NEXT;
    }
    else
    {
      eff=entree;
      entree=entree->NEXT;
    }
    if(!eff)
    {
      fprintf(stderr,"eff=null\n");
      exit(-1);
    }
    eff->NEXT=NULL;
    freechain(eff);
  }

#ifdef BUILDRCNDEBUG
{
  chain_list	*scan;
  for(scan=sortie;scan;scan=scan->NEXT)
    fprintf(stderr,"znc : (%ld,%ld)-(%ld,%ld) [%ld] lonode :%ld\n",
      ((znc*)(scan->DATA))->x1,
      ((znc*)(scan->DATA))->y1,
      ((znc*)(scan->DATA))->x2,
      ((znc*)(scan->DATA))->y2,
      ((znc*)(scan->DATA))->layer,
      ((znc*)(scan->DATA))->node);
}
#endif
  return(sortie);
}
