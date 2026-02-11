vImage2Papersize(imagedata_type *pImg)
{
	static int	iNetPageHeight = -1;
	static int	iNetPageWidth = -1;
	options_type	tOptions;
        double  dVerFactor, dHorFactor, dFactor;

	DBG_MSG("vImage2Papersize");

	fail(pImg == NULL);

	if (iNetPageHeight < 0 || iNetPageWidth < 0) {

		vGetOptions(&tOptions);

		iNetPageHeight = tOptions.iPageHeight -
				(lDrawUnits2MilliPoints(
					PS_TOP_MARGIN + PS_BOTTOM_MARGIN) +
					999) / 1000;
		iNetPageWidth = tOptions.iPageWidth -
				(lDrawUnits2MilliPoints(
					PS_LEFT_MARGIN + PS_RIGHT_MARGIN) +
					999) / 1000;
		DBG_DEC(iNetPageHeight);
		DBG_DEC(iNetPageWidth);
	}

	if (pImg->iVerSizeScaled < iNetPageHeight &&
	    pImg->iHorSizeScaled < iNetPageWidth) {

		return;
	}

	dVerFactor = (double)iNetPageHeight / (double)pImg->iVerSizeScaled;
	dHorFactor = (double)iNetPageWidth / (double)pImg->iHorSizeScaled;
        dFactor = min(dVerFactor, dHorFactor);
        DBG_FLT(dFactor);

        pImg->iVerSizeScaled = (int)(pImg->iVerSizeScaled * dFactor);
        pImg->iHorSizeScaled = (int)(pImg->iHorSizeScaled * dFactor);
}
