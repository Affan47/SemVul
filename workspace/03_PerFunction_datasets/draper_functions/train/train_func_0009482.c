find_postscript_font(FcPattern **fontpattern, char* fontname)
{
	FcPattern* font = NULL;
	size_t i;

	*fontpattern = NULL;
	for (i = 0; i < sizeof(postscript_alias)/sizeof(*postscript_alias); i++) {
		if (strcmp(fontname, postscript_alias[i].name) == 0) {
			FcChar8* family;

			FcPattern* pattern =
			    FcPatternBuild(0,
			                   FC_FAMILY, FcTypeString, postscript_alias[i].family,
			                   FC_STYLE, FcTypeString, postscript_alias[i].style,
			                   (char*)0);
			font = find_font(pattern);
			FcPatternDestroy(pattern);

			if (!font)
				return "fontconfig: Couldn't find font.";
			if (FcPatternGetString(font, FC_FAMILY, 0, &family) != FcResultMatch) {
				FcPatternDestroy(font);
				return "fontconfig: Couldn't retrieve font family name.";
			}


			if (strcmp((const char *)family, postscript_alias[i].family) != 0) {
				FcPatternDestroy(font);
				return "fontconfig: Didn't find expected font family. Perhaps URW Type 1 fonts need installing?";
			}
			break;
		}
	}

	*fontpattern = font;
	return NULL;
}
