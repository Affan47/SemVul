generate_RCN(fig)
lofig_list *fig;


{
  losig_list    *ScanSignal;

  fflush(stdout);
  fflush(stderr);

  SigMark( fig);

  if(rcnlynxdebug)
  {
    fflush(stderr);
    fprintf(stderr,"\n\n--------- DEBUT DE LA FONCTION generate_RCN -----------\n");
    fflush(stderr);
  }

  printf("\t---> Net extract is running...\n"); fflush(stdout);

  if(rcnlynxdebug)
  {
    fprintf(stderr,"Figure d'entree\n");
    Grgdisplay_datain(fig);
    fprintf(stderr,"____________________________________________\n");
    fflush(stderr);
  }

  if(rcnlynxchk)
  {
    if(rcnlynxdebug)
      fprintf(stderr,
	      "Verification de la conformite des structures d'entree...\n");
    GrgChkInConFEqui(fig);
  }


  GrgDualConLoPh(fig);


  GrgGroupVia(fig);

  if(rcnlynxchk)
  {
    if(rcnlynxdebug)
      fprintf(stderr,"Verification de la conformite des structures de travail...\n");
    GrgChkOutConVia(fig,rcnlynxdebug);
  }

  if(rcnlynxdebug)
  {
    fprintf(stderr,"Figure apres liaisons connecteur physique-logique\n");
    Grgdisplay_datain(fig);
    fprintf(stderr,"____________________________________________\n");
    fflush(stderr);
  }

  for(ScanSignal=fig->LOSIG; ScanSignal; ScanSignal=ScanSignal->NEXT)
  {


    GrgNodeINDEX=1L;

    buildrcn(fig,ScanSignal);


  }


  if(rcnlynxdebug)
  {
    fprintf(stderr,"-------- SORTIE DE LA FONCTION generate_RCN -----------\n");
  }

  fflush(stderr);
  fflush(stdout);

}
