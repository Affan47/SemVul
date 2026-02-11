doinit()
{

  inputnumbersfreq(phylofreq, &spp, &loci, &nonodes2, 2);
  if (printdata)
    fprintf(outfile, "\n%4ld Populations, %4ld Loci\n", spp, loci);
  alloctree(&curtree.nodep, nonodes2);
  if (!usertree) {
    alloctree(&bestree.nodep, nonodes2);
    alloctree(&priortree.nodep, nonodes2);
    if (njumble > 1) {
      alloctree(&bestree2.nodep, nonodes2);
    }
  }
  allocrest();
}
