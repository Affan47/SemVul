test3(int argc, char **argv) {
  FXApp a("libtest","Martin Preuss");
  FOX16_HtmlLabel *label;
  FOX16_Gui *gui;
  FXDialogBox *dbox;
  FXVerticalFrame *vf;
  const char testString[]=
#if 1
    "<h1>Title</h1>"
    "<h2>Subtitle</h2>"
    "This is <b>a</b> test. "
    "And this, is the second line: followed by something else."
    "<right>This should be right aligned</right>"
    "<table>"
    "  <tr>"
    "    <th>header1</th>"
    "    <th>header2</th>"
    "  </tr>"
    "  <tr>"
    "    <td>data1</td>"
    "    <td>this is longer data (data2)</td>"
    "  </tr>"
    "</table>"
    "And   this is   after the table.<br>"
    "and this <font color=\"red\">one</font> is red.";
#else
    "This is before right"
    "<right>Right</right>"
    "and this after right.";
#endif
  a.init(argc,argv);
  a.create();

  gui=new FOX16_Gui(&a);
  GWEN_Gui_SetGui(gui->getCInterface());

  dbox=new FXDialogBox(&a, "Test", DECOR_ALL);
  vf=new FXVerticalFrame(dbox, LAYOUT_FILL_X | LAYOUT_FILL_Y,
                         0, 0, 0, 0, 1, 1, 1, 1);
  label=new FOX16_HtmlLabel(vf, FXString(testString), LAYOUT_FILL_X|LAYOUT_FILL_Y);
  new FXSpring(vf, LAYOUT_FILL_X | LAYOUT_FILL_Y);
  new FXLabel(vf, "Normal Testlabel");

  dbox->create();
  dbox->resize(300, 200);
  dbox->show();
  a.runModalFor(dbox);

  return 0;
}
