ArtTreeRedraw(Widget gw)
{
    ArtTreeWidget	w = (ArtTreeWidget)gw;

    if (w->arttree.rubberbanding) {
	w->arttree.rubberbanding = False;
	draw_rubberband(w);
    }
    XClearArea(XtDisplay(w), XtWindow(w), 0, 0,
			 w->core.width, w->core.height, True);
}
