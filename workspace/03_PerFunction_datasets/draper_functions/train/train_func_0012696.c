test1(int argc, char **argv) {
  QApplication a(argc, argv);
  QT4_Gui *gui;
  int rv;
  GWEN_DIALOG *dlg;

  rv=GWEN_Init();
  if (rv) {
    DBG_ERROR_ERR(0, rv);
    return 2;
  }

  GWEN_Logger_SetLevel(0, GWEN_LoggerLevel_Info);


  gui=new QT4_Gui();
  GWEN_Gui_SetGui(gui->getCInterface());

  dlg=Dlg_Test1_new();
  if (dlg==NULL) {
    fprintf(stderr, "Could not create dialog.\n");
    return 2;
  }

  rv=GWEN_Gui_ExecDialog(dlg, 0);
  fprintf(stderr, "Result: %d\n", rv);

  return 0;
}
