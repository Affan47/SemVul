qmonCreateMainMenu(
Widget parent
) {
   Arg args[5];
   int ac;
   Widget MenuBar;

   DENTER(GUI_LAYER, "qmonCreateMainMenu");

   ac = 0;
   XtSetArg(args[ac], XmtNitems, menubar_items); ac++;
   XtSetArg(args[ac], XmtNnumItems, XtNumber(menubar_items)); ac++;

   MenuBar = XmtCreateMenubar(parent, "MainMenuBar", args, ac);

   DEXIT;
   return MenuBar;
}
