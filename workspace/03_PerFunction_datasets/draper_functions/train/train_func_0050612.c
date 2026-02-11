ConvertBidiCode(UCharDirection diricu, utf16 wUnicode)
{
	std::string staCode;

	switch (diricu)
	{
	case U_LEFT_TO_RIGHT:				return kdircL;
	case U_RIGHT_TO_LEFT:				return kdircR;
	case U_EUROPEAN_NUMBER:				return kdircEuroNum;
	case U_EUROPEAN_NUMBER_SEPARATOR:	return kdircEuroSep;
	case U_EUROPEAN_NUMBER_TERMINATOR:	return kdircEuroTerm;
	case U_ARABIC_NUMBER:				return kdircArabNum;
	case U_COMMON_NUMBER_SEPARATOR:		return kdircComSep;
	case U_WHITE_SPACE_NEUTRAL:			return kdircWhiteSpace;
	case U_OTHER_NEUTRAL:				return kdircNeutral;
	case U_LEFT_TO_RIGHT_EMBEDDING:		return kdircLRE;
	case U_LEFT_TO_RIGHT_OVERRIDE:		return kdircLRO;
	case U_RIGHT_TO_LEFT_ARABIC:		return kdircRArab;
	case U_RIGHT_TO_LEFT_EMBEDDING:		return kdircRLE;
	case U_RIGHT_TO_LEFT_OVERRIDE:		return kdircRLO;
	case U_POP_DIRECTIONAL_FORMAT:		return kdircPDF;
	case U_DIR_NON_SPACING_MARK:		return kdircNSM;
	case U_BOUNDARY_NEUTRAL:			return kdircBndNeutral;

	case U_BLOCK_SEPARATOR:				staCode = "B"; break;
	case U_SEGMENT_SEPARATOR:			staCode = "S"; break;
	default:
		char rgch[20];
		itoa(diricu, rgch, 10);
		staCode = rgch;
		break;
	}

	if (Bidi())
	{
		g_errorList.AddWarning(4510, NULL,
			"Default Unicode bidi char type for 0x",
			GdlGlyphDefn::UsvString(wUnicode), " = ", staCode,
			", which is not handled; char will be treated as neutral (ON)");
	}


	return kdircNeutral;
}
