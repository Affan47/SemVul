parseCssDeclaration( const unsigned char **position, cssKind kind, const char *aname)
{
	const unsigned char *cp = *position;
	vString *name = vStringNew ();
	vStringCopyS(name, aname);


	while ( isCssDeclarationAllowedChar(cp) ||
			*cp == '\0' )
	{
		if( *cp == ',' )
		{
			makeCssSimpleTag(name, kind, TRUE);
			*position = cp;
			return P_STATE_NONE;
		}
		else if( *cp == '{' || *cp == '\0' )
		{
			makeCssSimpleTag(name, kind, TRUE);
			*position = cp;
			return P_STATE_IN_DEFINITION;
		}

		vStringPut (name, (int) *cp);
		++cp;
	}

	makeCssSimpleTag(name, kind, TRUE);
	*position = cp;

	return P_STATE_NONE;
}
