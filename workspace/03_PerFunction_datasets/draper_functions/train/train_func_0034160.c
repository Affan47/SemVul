redrawWindowIfNeeded()
{
    if (RGBtransferWindow->visible()) {
	dbgprintf("Forcing the recalculation of the map LUT\n");
	RGBtransferBox->forceBuildMap();
        RGBtransferWindow->redraw();

    }

    return;
}
