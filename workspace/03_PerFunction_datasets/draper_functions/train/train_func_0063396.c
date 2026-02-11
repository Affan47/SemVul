sip_get_image_size(const qfits_header* hdr, int* pW, int* pH) {
	int W, H;
    W = qfits_header_getint(hdr, "IMAGEW", 0);
	debug("sip_get_image_size: IMAGEW = %i\n", W);
    H = qfits_header_getint(hdr, "IMAGEH", 0);
	debug("sip_get_image_size: IMAGEH = %i\n", H);
    if (!W) {
        W = qfits_header_getint(hdr, "NAXIS1", 0);
		debug("sip_get_image_size: NAXIS1 = %i\n", W);
	}
    if (!H) {
        H = qfits_header_getint(hdr, "NAXIS2", 0);
		debug("sip_get_image_size: NAXIS2 = %i\n", H);
	}
	if (pW) *pW = W;
	if (pH) *pH = H;
	return 0;
}
