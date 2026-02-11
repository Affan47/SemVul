vxml_is_valid_name_start_char(uint32 uc)
{


	if (VXC_COLON == uc || 0x5FU == uc)
		return TRUE;
	else if (uc >= 0x41U && uc <= 0x5AU)
		return TRUE;
	else if (uc >= 0x61U && uc <= 0x7AU)
		return TRUE;
	else if (uc >= 0xC0U && uc <= 0xD6U)
		return TRUE;
	else if (uc >= 0xD8U && uc <= 0xF6U)
		return TRUE;
	else if (uc >= 0xF8U && uc <= 0x2FFU)
		return TRUE;
	else if (uc >= 0x370U && uc <= 0x37DU)
		return TRUE;
	else if (uc >= 0x37FU && uc <= 0x1FFFU)
		return TRUE;
	else if (uc >= 0x200CU && uc <= 0x200DU)
		return TRUE;
	else if (uc >= 0x2070U && uc <= 0x218FU)
		return TRUE;
	else if (uc >= 0x2C00U && uc <= 0x2FEFU)
		return TRUE;
	else if (uc >= 0x3001U && uc <= 0xD7FFU)
		return TRUE;
	else if (uc >= 0xF900U && uc <= 0xFDCFU)
		return TRUE;
	else if (uc >= 0xFDF0U && uc <= 0xFFFDU)
		return TRUE;
	else if (uc >= 0x10000U && uc <= 0xEFFFFU)
		return TRUE;
	else
		return FALSE;
}
