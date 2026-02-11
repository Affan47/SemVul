status_for_code (gchar code)
{
	switch (code) {
	case 'o':
		return _("Unknown");
	case 'i':
		return _("Invalid");
	case 'd':
		return C_("ownertrust", "Disabled");
	case 'r':
		return _("Revoked");
	case 'e':
		return _("Expired");
	case 'q': case '-':
		return _("Undefined trust");
	case 'n':
		return _("Distrusted");
	case 'm':
		return _("Marginally trusted");
	case 'f':
		return _("Fully trusted");
	case 'u':
		return _("Ultimately trusted");
	default:
		return NULL;
	}
}
