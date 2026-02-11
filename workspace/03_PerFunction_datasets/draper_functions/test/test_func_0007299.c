endSelection(obj, abort)
CannaObject obj;
int abort;
{
    ICSelectionControlArg arg;
    int selected;

    if (ignoreListfunc) return;
    arg.command = ICSelectionEnd;
    arg.u.current_item = -1;
    XtCallCallbackList((Widget)obj, obj->inputConv.selectioncallback,
		       (XtPointer)&arg);

    if (!abort && (selected = arg.u.current_item) >= 0) {
        insertSelection(obj, selected);
    }
}
