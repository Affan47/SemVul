add_sip_coeffs(qfits_header* hdr, const char* prefix, const sip_t* sip) {
	char key[64];
	int m, n, order;

	if (sip->a_order) {
		sprintf(key, "%sSAO", prefix);
		order = sip->a_order;
		fits_header_add_int(hdr, key, order, "SIP forward polynomial order");
		for (m=0; m<=order; m++) {
			for (n=0; (m+n)<=order; n++) {
				if (m+n < 1)
					continue;
				sprintf(key, "%sA%i%i", prefix, m, n);
				fits_header_add_double(hdr, key, sip->a[m][n], "");
				sprintf(key, "%sB%i%i", prefix, m, n);
				fits_header_add_double(hdr, key, sip->b[m][n], "");
			}
		}
	}
	if (sip->ap_order) {
		order = sip->ap_order;
		sprintf(key, "%sSAPO", prefix);
		fits_header_add_int(hdr, key, order, "SIP reverse polynomial order");
		for (m=0; m<=order; m++) {
			for (n=0; (m+n)<=order; n++) {
				if (m+n < 1)
					continue;
				sprintf(key, "%sAP%i%i", prefix, m, n);
				fits_header_add_double(hdr, key, sip->ap[m][n], "");
				sprintf(key, "%sBP%i%i", prefix, m, n);
				fits_header_add_double(hdr, key, sip->bp[m][n], "");
			}
		}
	}
}
