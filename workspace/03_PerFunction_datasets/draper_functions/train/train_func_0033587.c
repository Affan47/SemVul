XmtCliWrite(Widget w, String s, int n)
#else
static void XmtCliWrite(w, s, n)
Widget w;
String s;
int n;
#endif
{
    XmtCliWidget cw = (XmtCliWidget) w;
    wchar_t wcs[8*BUFSIZ];
    int mblen = 0;

    mbstowcs(wcs, s, 8*BUFSIZ-1);
#ifndef DARWIN
    mblen = wcslen(wcs);
#else
    mblen = strlen(s);
#endif


    XmTextReplaceWcs(w, cw->cli.inputpos, cw->cli.inputpos + mblen, wcs);


    cw->cli.inputpos += mblen;


    if (XmTextGetInsertionPosition(w) < cw->cli.inputpos) {
	cw->cli.permissive = True;
	XmTextSetInsertionPosition(w, cw->cli.inputpos);
	cw->cli.permissive = False;
    }

    if (!cw->cli.paging) {
	XmTextShowPosition(w, XmTextGetLastPosition(w));


	if (cw->cli.total_lines > cw->cli.save_lines + (cw->cli.save_lines>>1))
	    TrimLines(cw);
    }
}
