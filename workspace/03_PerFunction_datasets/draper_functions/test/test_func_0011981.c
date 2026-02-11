vEpilogue(diagram_type *pDiag)
{
	switch (eConversionType) {
	case conversion_text:
	case conversion_fmt_text:
		vEpilogueTXT(pDiag->pOutFile);
		break;
	case conversion_ps:
		vEpiloguePS(pDiag);
		break;
	case conversion_xml:
		vEpilogueXML(pDiag);
		break;
	case conversion_pdf:
		vEpiloguePDF(pDiag);
		break;
	default:
		DBG_DEC(eConversionType);
		break;
	}
}
