SelectionStart(ocw, kind)
OffTheSpotConversionWidget ocw;
int kind;
{
    Cardinal ncand;

    TRACE(("OffTheSpotConversion:SelectionStart()\n"));
    if (ocw->offthespot.selectionpoppedup) {
	TRACE(("\tselection already started -- ignored\n"));
	return;
    }

    ocw->offthespot.candlist = ICGetItemList(ocw->ccontrol.inputobj, &ncand);
    ocw->offthespot.numcands = ncand;

    TRACE(("\tnumcands=%d\n", ocw->offthespot.numcands));
    CPanelSetList(ocw->offthespot.selectionwidget,
		  ocw->offthespot.candlist,
		  ocw->offthespot.numcands, 0, True);


    LocateSelectionPopup(ocw);

    XtPopup(ocw->offthespot.selectionshell, XtGrabNone);
    ocw->offthespot.selectionpoppedup = True;
}
