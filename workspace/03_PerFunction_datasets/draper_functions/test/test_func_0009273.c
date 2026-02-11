XmtChooserLookupItemByName(Widget w, StringConst name)
#else
int XmtChooserLookupItemByName(w, name)
Widget w;
StringConst name;
#endif
{
   XmtChooserWidget cw = (XmtChooserWidget)w;
   int i;

   XmtAssertWidgetClass(w, xmtChooserWidgetClass,"XmtChooserLookupItemByName");

   if (!name || !cw->chooser.strings) return -1;

   for(i = cw->chooser.num_items-1; i >= 0; i--)
       if (cw->chooser.strings[i] && (strcmp(name, cw->chooser.strings[i])==0))
	   break;

   return i;
}
