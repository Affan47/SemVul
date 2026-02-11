SelectItem(w, n)
Widget w;
int n;
{
    CcWnnObject obj = (CcWnnObject)w;
    int ret = 0;

    if (obj->ccWnn.state == normal_state) return -1;

    if (obj->ccWnn.jcbuf == NULL) {
	ret = -1;
    } else if (n >= 0) {
	ret = insertSelection(obj, n);
	if (obj->ccWnn.textchanged) {
	    XtCallCallbackList((Widget)obj,
			       obj->inputConv.textchangecallback,
			       (XtPointer)NULL);
	    obj->ccWnn.textchanged = False;
	}
    }

    obj->ccWnn.state = normal_state;
    return ret;
}
