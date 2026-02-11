ReleaseSymbol(XmtChooserWidget cw)
#else
static void ReleaseSymbol(cw)
XmtChooserWidget cw;
#endif
{
    if (cw->chooser.symbol) {
	XmtSymbolRemoveCallback(cw->chooser.symbol,
				ValueChanged, (XtPointer)cw);
	cw->chooser.symbol = NULL;
    }
}
