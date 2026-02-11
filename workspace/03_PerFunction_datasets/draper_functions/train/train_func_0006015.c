_XmtDialogPopdownCallback(Widget w, XtPointer tag, XtPointer data)
#else
void _XmtDialogPopdownCallback(w, tag, data)
Widget w;
XtPointer tag;
XtPointer data;
#endif
{
    XmtDialogCache *cache = (XmtDialogCache *)tag;
    Widget dialog;


    if (cache->in_use < cache->num) {
	int i;


	dialog = ((CompositeWidget)w)->composite.children[0];
	for(i=0; i < cache->num; i++)
	    if (cache->dialogs[i] == dialog) break;

	XtDestroyWidget(dialog);


	for(; i < cache->num-1; i++) cache->dialogs[i] = cache->dialogs[i+1];

	cache->num--;
    }

    cache->in_use--;
}
