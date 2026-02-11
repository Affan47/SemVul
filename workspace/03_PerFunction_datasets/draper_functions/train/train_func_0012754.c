test3(int argc, char **argv) {
  int rv;
  AB_BANKING *ab;
  GWEN_GUI *gui;

  rv=GWEN_Init();
  if (rv) {
    fprintf(stderr, "ERROR: Unable to init Gwen.\n");
    exit(2);
  }

  gui=GWEN_Gui_CGui_new();
  GWEN_Gui_SetGui(gui);

  ab=AB_Banking_new("testlib", NULL, 0);

  rv=AB_Banking_HasConf4(ab);
  if (!rv) {
    fprintf(stderr, "Config for AqBanking 4 found\n");
    return 0;
  }
  fprintf(stderr, "Config for AqBanking 4 not found (%d)\n", rv);

  rv=AB_Banking_HasConf3(ab);
  if (!rv) {
    fprintf(stderr, "Config for AqBanking 3 found, importing\n");
    rv=AB_Banking_ImportConf3(ab);
    if (rv<0) {
      fprintf(stderr, "Error importing configuration (%d)\n", rv);
      return 2;
    }
    return 0;
  }
  fprintf(stderr, "Config for AqBanking 3 not found (%d)\n", rv);

  rv=AB_Banking_HasConf2(ab);
  if (!rv) {
    fprintf(stderr, "Config for AqBanking 2 found, importing\n");
    rv=AB_Banking_ImportConf3(ab);
    if (rv<0) {
      fprintf(stderr, "Error importing configuration (%d)\n", rv);
      return 2;
    }
    return 0;
  }
  fprintf(stderr, "Config for AqBanking 2 not found (%d)\n", rv);

  return 0;
}
