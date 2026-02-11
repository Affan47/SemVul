rescan_fits_wcs(struct ccd_frame *fr, struct wcs *fim)
{
	g_return_if_fail(fr != NULL);
	g_return_if_fail(fim != NULL);

	fim->wcsset = WCS_INITIAL;
	fim->flags &= ~WCS_HINTED;
	fim->flags &= ~WCS_USE_LIN;

	if (fits_get_double(fr, P_STR(FN_CRPIX1), &fim->xrefpix) <= 0)
		fim->wcsset = WCS_INVALID;
	if (fits_get_double(fr, P_STR(FN_CRPIX2), &fim->yrefpix) <= 0)
		fim->wcsset = WCS_INVALID;
	if (fits_get_double(fr, P_STR(FN_CRVAL1), &fim->xref) <= 0)
		fim->wcsset = WCS_INVALID;
	if (fits_get_double(fr, P_STR(FN_CRVAL2), &fim->yref) <= 0)
		fim->wcsset = WCS_INVALID;
	if (fits_get_double(fr, P_STR(FN_EQUINOX), &fim->equinox) <= 0)
		fim->equinox = 2000;
	if (!scan_for_CD(fr, fim))
		if (!scan_for_PC(fr, fim))
			fim->wcsset = WCS_INVALID;

	d3_printf("wcs status is: %d\n", fim->wcsset);
}
