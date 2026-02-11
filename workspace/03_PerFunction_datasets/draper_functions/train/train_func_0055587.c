addwinznc(elem,wininfo)
znc		*elem;
WinZnc		*wininfo;
{
  long		 x1,y1,x2,y2;
  long		 nx1,ny1;
  chain_list	*ptchain;


  x1=getmx(elem,wininfo);
  y1=getmy(elem,wininfo);
  x2=getMx(elem,wininfo);
  y2=getMy(elem,wininfo);


  for(nx1=x1;nx1<=x2;nx1++)
  {
    for(ny1=y1;ny1<=y2;ny1++)
    {

#ifdef ZNCDEBUG
fprintf(stderr,"Ajout de l'element dans la fenetre %ld\n",ny1*wininfo->nx + nx1);
#endif

      ptchain=*(wininfo->ChZnc + ny1*wininfo->nx + nx1);
      ptchain=addchain(ptchain,elem);
      *(wininfo->ChZnc + ny1*wininfo->nx + nx1)=ptchain;


     elem->Win=addchain(elem->Win,wininfo->ChZnc + ny1*wininfo->nx + nx1);
    }
  }
}
