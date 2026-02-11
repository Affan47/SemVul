gn_phonebook_number_type2str(gn_phonebook_number_type t)
{
	switch (t) {
	case GN_PHONEBOOK_NUMBER_None:		return _("General number");
	case GN_PHONEBOOK_NUMBER_Common:	return _("General number");
	case GN_PHONEBOOK_NUMBER_Home:		return _("Home number");
	case GN_PHONEBOOK_NUMBER_Mobile:	return _("Mobile number");
	case GN_PHONEBOOK_NUMBER_Fax:		return _("Fax number");
	case GN_PHONEBOOK_NUMBER_Work:		return _("Work number");
	case GN_PHONEBOOK_NUMBER_General:	return _("General number");
	default:				return _("Unknown number");
	}
}
