EncodeFlags(char *trusts, unsigned int flags)
{
    if (flags & CERTDB_VALID_CA)
	if (!(flags & CERTDB_TRUSTED_CA) &&
	    !(flags & CERTDB_TRUSTED_CLIENT_CA))
	    PORT_Strcat(trusts, "c");
    if (flags & CERTDB_TERMINAL_RECORD)
	if (!(flags & CERTDB_TRUSTED))
	    PORT_Strcat(trusts, "p");
    if (flags & CERTDB_TRUSTED_CA)
	PORT_Strcat(trusts, "C");
    if (flags & CERTDB_TRUSTED_CLIENT_CA)
	PORT_Strcat(trusts, "T");
    if (flags & CERTDB_TRUSTED)
	PORT_Strcat(trusts, "P");
    if (flags & CERTDB_USER)
	PORT_Strcat(trusts, "u");
    if (flags & CERTDB_SEND_WARN)
	PORT_Strcat(trusts, "w");
    if (flags & CERTDB_INVISIBLE_CA)
	PORT_Strcat(trusts, "I");
    if (flags & CERTDB_GOVT_APPROVED_CA)
	PORT_Strcat(trusts, "G");
    return;
}
