emboss_getoptions(char *pgm, int argc, char *argv[])
{
  ajint numseqs=0;
  ajint numwts=0;
  AjPStr method = NULL;


  howoften = often;
  howmany = many;
  outgrno = 1;
  outgropt = false;
  simple = true;
  trout = true;
  weights = false;
  justwts = false;
  ancvar = false;
  allsokal = false;
  allwagner = true;
  mixture = false;
  printdata = false;
  progress = true;
  treeprint = true;
  stepbox = false;
  ancseq = false;
  mulsets = false;
  msets = 1;

  embInitPV(pgm, argc, argv, "PHYLIPNEW",VERSION);

    phylostates = ajAcdGetDiscretestates("infile");

    while (phylostates[numseqs])
	numseqs++;

    phyloweights = ajAcdGetProperties("weights");
    if (phyloweights)
    {
      weights = true;
      numwts = ajPhyloPropGetSize(phyloweights);
    }

    if (numseqs > 1) {
	mulsets = true;
        msets = numseqs;
    }
    else if (numwts > 1) {
      mulsets = true;
      msets = numwts;
      justwts = true;
    }

    phyloanc = ajAcdGetProperties("ancfile");
    if(phyloanc) ancvar = true;

    method = ajAcdGetListSingle("method");

    if(ajStrMatchC(method, "w")) allwagner = true;
    else if(ajStrMatchC(method, "c")) allsokal = true;
    else if(ajStrMatchC(method, "m")) {
      mixture = allwagner = true;
      phylomix = ajAcdGetProperties("mixfile");
    }

    howmany = ajAcdGetInt("howmany");
    howoften = ajAcdGetInt("howoften");

    outgrno = ajAcdGetInt("outgrno");
    if(outgrno != 0) outgropt = true;
    else outgrno = 1;

    simple = ajAcdGetBoolean("simple");


    threshold = ajAcdGetFloat("threshold");

    progress = ajAcdGetBoolean("progress");
    printdata = ajAcdGetBoolean("printdata");
    treeprint = ajAcdGetBoolean("treeprint");
    trout = ajAcdGetToggle("trout");
    stepbox = ajAcdGetBoolean("stepbox");
    ancseq = ajAcdGetBoolean("ancseq");

     embossoutfile = ajAcdGetOutfile("outfile");
     emboss_openfile(embossoutfile, &outfile, &outfilename);

     if(trout) {
       embossouttree = ajAcdGetOutfile("outtreefile");
       emboss_openfile(embossouttree, &outtree, &outtreename);
     }

  fprintf(outfile, "\nPenny algorithm, version %s\n",VERSION);
  fprintf(outfile, " branch-and-bound to find all");
  fprintf(outfile, " most parsimonious trees\n\n");

}
