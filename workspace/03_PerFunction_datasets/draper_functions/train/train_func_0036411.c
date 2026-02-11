vPrologue2(diagram_type *pDiag, int iWordVersion)
{
	switch (eConversionType) {
	case conversion_text:
	case conversion_fmt_text:
		break;
	case conversion_ps:
		vAddFontsPS(pDiag);
		break;
	case conversion_xml:
		vCreateBookIntro(pDiag, iWordVersion);
		break;
	case conversion_pdf:
		vCreateInfoDictionary(pDiag, iWordVersion);
		vAddFontsPDF(pDiag);
		break;
	default:
		DBG_DEC(eConversionType);
		break;
	}
}
