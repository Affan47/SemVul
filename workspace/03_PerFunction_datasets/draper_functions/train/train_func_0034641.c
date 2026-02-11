isCssDeclarationAllowedChar( const unsigned char *cp )
{
	return  isalnum ((int) *cp) ||
			isspace ((int) *cp) ||
			*cp == '_' ||
			*cp == '-' ||
			*cp == '+' ||
			*cp == '>' ||
			*cp == '{' ||
			*cp == '.' ||
			*cp == ',' ||
			*cp == ':' ||
			*cp == '*' ||
			*cp == '#';
}
