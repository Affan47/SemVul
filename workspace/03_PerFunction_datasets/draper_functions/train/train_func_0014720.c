bAddDummyImagePDF(diagram_type *pDiag, const imagedata_type *pImg)
{
	FILE	*pOutFile;

	fail(pDiag == NULL);
	fail(pDiag->pOutFile == NULL);
	fail(pImg == NULL);

	if (pImg->iVerSizeScaled <= 0 || pImg->iHorSizeScaled <= 0) {
		return FALSE;
	}

	iImageCount++;

	DBG_DEC_C(pDiag->lXleft != 0, pDiag->lXleft);

	pDiag->lYtop -= lPoints2DrawUnits(pImg->iVerSizeScaled);
	vMoveTo(pDiag, lPoints2DrawUnits(pImg->iVerSizeScaled));

	pOutFile = pDiag->pOutFile;

	vFPprintf(pOutFile, "ET\n");
	vFPprintf(pOutFile, "q %% Image %03d\n", iImageCount);
	vFPprintf(pOutFile, "\t1.0 w\n");
	vFPprintf(pOutFile, "\t0.3 G\n");
	vFPprintf(pOutFile, "\t%.2f %.2f %d %d re\n",
			dDrawUnits2Points(pDiag->lXleft + PS_LEFT_MARGIN),
			dDrawUnits2Points(pDiag->lYtop),
			pImg->iHorSizeScaled,
			pImg->iVerSizeScaled);
	vFPprintf(pOutFile, "\tS\n");
	vFPprintf(pOutFile, "Q\n");
	vFPprintf(pOutFile, "BT\n");

	pDiag->lXleft = 0;

	return TRUE;
}
