scanWertOption(int &argc, char *argv[], const char * name,
		    optionsVerwalter* verwalter) {
  for (int i=1; i<argc; i++) {
    int j;
    for (j=0; (name[j]==0 ? 0 : argv[i][j]==name[j]); j++) {}
    if (name[j]==0) {
      if (argv[i][j]==0 && i+1<argc) {
        (*verwalter)(argv[i+1]);
        argc-=2;
        for (j=i; j<argc; j++)
          argv[j]=argv[j+2];
        return;
      }
      if (argv[i][j]=='=') {
        (*verwalter)(argv[i]+j+1);
        argc-=1;
        for (j=i; j<argc; j++)
          argv[j]=argv[j+1];
        return;
      }
    }
  }
}
