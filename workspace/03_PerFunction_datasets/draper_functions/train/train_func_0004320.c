UT_isSmartQuotedCharacter(UT_UCSChar c)
{
	bool result;
	switch (c)
	{
	case UCS_LQUOTE:
	case UCS_RQUOTE:
	case UCS_LDBLQUOTE:
	case UCS_RDBLQUOTE:
	case 0x201a:
	case 0x201e:
	case 0x2039:
	case 0x203a:
	case 0x300c:
	case 0x300d:
	case 0x300e:
	case 0x300f:
	case '\"':
	case '\'':
		result = true;
		break;
	default:
		result = false;
		break;
	}
	return (result);
}
