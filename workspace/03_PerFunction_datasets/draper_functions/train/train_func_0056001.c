test2(int argc, char **argv) {
  QApplication a(argc, argv);
  QT4_Gui *gui;
  QString lf;
  int rv;
  uint32_t pid;

  rv=GWEN_Init();
  if (rv) {
    DBG_ERROR_ERR(0, rv);
    return 2;
  }

  GWEN_Logger_SetLevel(0, GWEN_LoggerLevel_Info);


  gui=new QT4_Gui();
  GWEN_Gui_SetGui(gui->getCInterface());


#if 0
  pid=GWEN_Gui_ProgressStart(GWEN_GUI_PROGRESS_SHOW_PROGRESS | GWEN_GUI_PROGRESS_KEEP_OPEN,
			     "Progress-Title",
			     "This is an example progress with 2 steps"
			     "<html>This is an <strong>example</strong> progress with 2 steps</html>",
			     2,
			     0);
#else
  pid=GWEN_Gui_ProgressStart(GWEN_GUI_PROGRESS_SHOW_PROGRESS | GWEN_GUI_PROGRESS_KEEP_OPEN,
			     "Progress-Title",
			     "This is an <b>example</b> progress with 2 steps",
			     2,
			     0);
#endif

  GWEN_Gui_ProgressAdvance(pid, 1);
  rv=GWEN_Gui_MessageBox(GWEN_GUI_MSG_FLAGS_TYPE_INFO,
			 "MessageBox-Title",
			 "This message box should appear in the context of the open progress dialog",
			 "Button1",
			 "Button2",
			 "Button3",
			 pid);
  GWEN_Gui_ProgressAdvance(pid, 2);
  GWEN_Gui_ProgressEnd(pid);

  return 0;
}
