eap_print(netdissect_options *ndo,
	  register const u_char *cp,
	  u_int length _U_)
{
	const struct eap_packet_t *eap;

	eap = (const struct eap_packet_t *)cp;
	ND_TCHECK(eap->data);

        ND_PRINT((ndo, "EAP code=%u id=%u length=%u ",
		  eap->code, eap->id, (eap->length[0]<<8) + eap->length[1]));

        if (!ndo->ndo_vflag)
            return;

trunc:
	;
}
