isSubroutineDeclaration (const unsigned char *cp)
{
	boolean attr = FALSE;
	int nparens = 0;

	do {
		for ( ; *cp; ++cp) {
SUB_DECL_SWITCH:
			switch (*cp) {
				case ':':
					if (nparens)
						break;
					else if (TRUE == attr)
						return FALSE;
					else
						attr = TRUE;
					break;
				case '(':
					++nparens;
					break;
				case ')':
					--nparens;
					break;
				case ' ':
				case '\t':
					break;
				case ';':
					if (!nparens)
						return TRUE;
				case '{':
					if (!nparens)
						return FALSE;
				default:
					if (attr) {
						if (isIdentifier1(*cp)) {
							cp++;
							while (isIdentifier (*cp))
								cp++;
							attr = FALSE;
							goto SUB_DECL_SWITCH;
						} else {
							return FALSE;
						}
					} else if (nparens) {
						break;
					} else {
						return FALSE;
					}
			}
		}
	} while (NULL != (cp = fileReadLine ()));

	return FALSE;
}
