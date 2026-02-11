create_fontfamily_from_collection (char* name, GpFontCollection *font_collection, GpFontFamily **fontFamily)
{

	if (font_collection->fontset) {
		int i;
		FcChar8 *str;
		FcPattern **gpfam = font_collection->fontset->fonts;

		for (i=0; i < font_collection->fontset->nfont; gpfam++, i++) {
			FcResult rlt = FcPatternGetString (*gpfam, FC_FAMILY, 0, &str);
			GpStatus status = gdip_status_from_fontconfig (rlt);
			if (status != Ok)
				return status;

			if (strcmp ((char *)name, (const char *)str) == 0) {
				gdip_createFontFamily (fontFamily);
				(*fontFamily)->pattern = *gpfam;
				(*fontFamily)->allocated = FALSE;
				return Ok;
			}
		}
	}
	return FontFamilyNotFound;
}
