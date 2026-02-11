parsed_description (GcrParsed *parsed,
                    CK_OBJECT_CLASS klass)
{
	g_assert (parsed != NULL);
	switch (klass) {
	case CKO_PRIVATE_KEY:
		parsed->description = _("Private Key");
		break;
	case CKO_CERTIFICATE:
		parsed->description = _("Certificate");
		break;
	case CKO_PUBLIC_KEY:
		parsed->description = _("Public Key");
		break;
	case CKO_GCR_GNUPG_RECORDS:
		parsed->description = _("PGP Key");
		break;
	case CKO_GCR_CERTIFICATE_REQUEST:
		parsed->description = _("Certificate Request");
		break;
	default:
		parsed->description = NULL;
		break;
	}
}
