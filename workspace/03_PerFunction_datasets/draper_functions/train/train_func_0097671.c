DNSNameEncode(char **Pos_pp, char *Name, uint16_t Offset)
{
	char *Pos_p;
	char *Name_p;
	char *Dot_p;
	size_t Len;

	if (NULL == Pos_pp ||
	    NULL == *Pos_pp ||
	    NULL == Name ||
	    strlen(Name) > DNS_NAME_SIZE)
		return DNS_RCODE_FORMERR;

	Pos_p = *Pos_pp;
	Name_p = Name;

	while ('\0' != *Name_p) {

		Dot_p = strchr(Name_p, '.');
		Len = (NULL != Dot_p) ? (size_t) (Dot_p - Name_p) : strlen(Name_p);
		if (Len) {

			*Pos_p++ = (uint8_t) Len;

			memcpy(Pos_p, Name_p, Len);
			Pos_p += Len;
			Name_p += Len;
		}

		if (NULL != Dot_p)
			Name_p++;
	}

	if (Offset) {

		ADD16(Pos_p, 0xc000 | Offset);
	} else
		*Pos_p++ = 0;

	*Pos_pp = Pos_p;

	return DNS_RCODE_NOERROR;
}
