add_root_to_options(CHAR16 *options, CHAR16 *root, CHAR16 *vmcode)
{
	CHAR16 *o, ko[CMDLINE_MAXLEN];

	if (vmcode[0]) {
		for (o = options; *o; o++) {
			if (*o == '-' && *(o+1) == '-')
				break;
		}
		if (! *o) {

			StrCpy(o, L" -- ");
			o++;
		}


		o += 2;
		while (*o == ' ') o++;
	} else {
		o = options;
	}


	StrCpy(ko, o);
	StrCpy(o, L"root=");
	StrCat(o, root);
	StrCat(o, L" ");
	StrCat(o, ko);
}
