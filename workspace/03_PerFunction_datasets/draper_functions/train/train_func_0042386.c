main(int argc, char* argv[]) {

  if (argc < 4) {
    printf("USAGE : rsem-preref refFastaF polyAChoice refName [-l polyALen] [-f exceptionF] [--no-ntog] [-q]\n\n");
    printf("  refFastaF: a FASTA format file contains all reference transcripts\n");
    printf("  polyAChoice: choice for polyA tail padding.It is a number from {0,1,2}\n");
    printf("    0: pad polyA tail\n");
    printf("    1: do not pad polyA tail at all\n");
    printf("    2: pad polyA tail for all references but those in exceptionF\n");
    printf("  -l: polyALen: specify the length of polyA tail you want to pad. Default is 100\n");
    printf("  -f: exceptionF: file contains a list of exception reference ids. IDs starts from 1. Must set if polyAChoice = 2\n");
    printf("  --no-ntog: do not convert N in references into G\n");
    printf("  -q: quiet\n");
    exit(-1);
  }


  polyAChoice = atoi(argv[2]);

  polyALen = 125;
  ntog = true;
  quiet = false;
  memset(exceptionF, 0, sizeof(exceptionF));

  for (int i = 4; i < argc; i++) {
	  if (!strcmp(argv[i], "-l")) { polyALen = atoi(argv[i + 1]); }
	  if (!strcmp(argv[i], "-f")) { strcpy(exceptionF, argv[i + 1]); }
	  if (!strcmp(argv[i], "--no-ntog")) { ntog = false; }
	  if (!strcmp(argv[i], "-q")) { quiet = true; }
  }

  verbose = !quiet;


  rules = PolyARules(polyAChoice, polyALen, exceptionF);
  refs.makeRefs(argv[1], refp, rules);
  M = refs.getM();


  sprintf(refF, "%s.seq", argv[3]);
  refs.saveRefs(refF);

  sprintf(alignerFastaF, "%s.idx.fa", argv[3]);
  fout.open(alignerFastaF);
  for (int i = 1; i <= M; i++) {
    fout<<">"<<refs.getRef(i).getName()<<endl<<(ntog ? aligner_refp.convert(refs.getRef(i).getSeq()) : refs.getRef(i).getSeq())<<endl;
  }
  fout.close();

  if (verbose) { printf("IDX.fa generated!\n"); }

  return 0;
}
