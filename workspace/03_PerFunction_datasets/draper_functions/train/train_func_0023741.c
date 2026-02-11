StringWidth(w, seg, start, end)
Widget w;
ICString *seg;
int start;
int end;
{
    WcharDisplayObject obj = (WcharDisplayObject)w;
    wchar *wstr;
    int len = seg->nchars;
    int nctl;
    int width;

    if (end < 0 || len < end) end = len;
    if (start >= end || start >= len) return 0;

    wstr = (wchar *)seg->data + start;
    len = end - start;


    if ((nctl = countControlChars(wstr, len)) == 0) {

	width = XWSTextWidth(obj->wcharDisplay.gcset_normal, wstr, len);
    } else {
	wchar *s = (wchar *)LOCAL_ALLOC(sizeof(wchar) * (len + nctl));

	expandControlChars(wstr, len, s);
	width = XWSTextWidth(obj->wcharDisplay.gcset_normal, s, len + nctl);
	LOCAL_FREE(s);
    }
    return width;
}
