emboss_getoptions(char *pgm, int argc, char *argv[])
{
  AjPStr method = NULL;
  AjPStr initialtree = NULL;

  how = arb;
  usertree = false;
  goteof = false;
  thresh = false;
  threshold = spp;
  weights = false;
  ancvar = false;
  factors = false;
  dollo = true;
  screenlines = 24;
  scrollinc   = 20;
  screenwidth = 80;

  embInitPV(pgm, argc, argv, "PHYLIPNEW",VERSION);

    phylostates = ajAcdGetDiscretestates("infile");

    phyloweights = ajAcdGetProperties("weights");
    if(phyloweights)  weights = true;

    phyloanc = ajAcdGetProperties("ancfile");
    if(phyloanc) ancvar = true;

    initialtree = ajAcdGetListSingle("initialtree");

    if(ajStrMatchC(initialtree, "a")) how = arb;
    if(ajStrMatchC(initialtree, "u")) how = use;
    if(ajStrMatchC(initialtree, "s")) {
      how = spec;
      phylotrees = ajAcdGetTree("intreefile");
      usertree = true;
    }

    phylofact = ajAcdGetProperties("factorfile");
    if(phylofact) factors = true;


    method = ajAcdGetListSingle("method");

    if(ajStrMatchC(method, "d")) dollo = true;
    else dollo = false;

    thresh = ajAcdGetToggle("dothreshold");
    if(thresh)  threshold = ajAcdGetFloat("threshold");


    screenwidth = ajAcdGetInt("screenwidth");
    screenlines = ajAcdGetInt("screenlines");


  if (scrollinc < screenwidth / 2.0)
    hscroll = scrollinc;
  else
    hscroll = screenwidth / 2;
  if (scrollinc < screenlines / 2.0)
    vscroll = scrollinc;
  else
    vscroll = screenlines / 2;
    printf("\nInteractive Dollo or polymorphism parsimony, version %s\n\n",VERSION);

     embossouttree = ajAcdGetOutfile("outtreefile");
     emboss_openfile(embossouttree, &outtree, &outtreename);


}
