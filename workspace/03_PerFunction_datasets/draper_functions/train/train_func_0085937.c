hook_toke_scan_word (pTHX_ int offset, int handle_package, char *dest, STRLEN destlen, STRLEN *res_len) {
	char *base_s = SvPVX (PL_linestr) + offset;
	return scan_word (base_s, dest, destlen, handle_package, res_len);
}
