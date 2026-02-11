isContextualStatement (const statementInfo *const st)
{
	boolean result = FALSE;
	if (st != NULL) switch (st->declaration)
	{
		case DECL_CLASS:
		case DECL_ENUM:
		case DECL_INTERFACE:
		case DECL_NAMESPACE:
		case DECL_STRUCT:
		case DECL_UNION:
			result = TRUE;
			break;

		default: result = FALSE; break;
	}
	return result;
}
