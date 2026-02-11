ChangeAttributes(w, mask, value)
Widget w;
unsigned long mask;
ConversionAttributes *value;
{
    OverTheSpotConversionWidget ocw = (OverTheSpotConversionWidget)w;
    ResetStatus dispres, tcres;

    TRACE(("OverTheSpot:ChangeAttributes()\n"));

    if (ocw->overthespot.ignorestatusarea) mask &= ~CAStatusArea;

    dispres = resetDisplayObject(ocw, mask, value);
    tcres = resetTextCanvas(ocw, mask, value);
    if (dispres == NeedReconfig || tcres == NeedReconfig) {
	redrawAndReconfigureTextCanvas(ocw);
    } else if (dispres == NeedRedraw || tcres == NeedRedraw) {
	TextCanvas *tcp = ocw->overthespot.canvaslist;

	while (tcp != NULL) {
	    if (XtIsRealized(tcp->canvas)) {
		XClearArea(XtDisplay(tcp->canvas), XtWindow(tcp->canvas),
			   0, 0, 0, 0, True);
	    }
	    tcp = tcp->next;
	}
    }

    if (resetModeWidget(ocw, mask, value) != NeedNone &&
	XtIsRealized(ocw->overthespot.modewidget)) {
	XClearArea(XtDisplay(w), XtWindow((Widget)ocw->overthespot.modewidget),
		   0, 0, 0, 0, True);
    }
}
