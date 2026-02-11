gammainput_cb(Fl_Float_Input *theInput, transfer *panel)
{
    double eval, val;
    const char  *cval;

    dbgprintf("Gamma input callback\n");

    cval = theInput->value();
    eval = atof(cval);
    if (eval > 0) {
	val = log(eval);
    } else {
	char cval[10];
	val = -1;
	sprintf(cval,"%1.4g", exp(-1));
	panel->setGammaInputValue((const char *)cval);
    }

    panel->setGammaSliderValue((float)val);
    panel->ensureImageRedraw(true);
    panel->setDrawingParms();

    return;
}
