ColorSpaceSignature2TiffInkset(
icColorSpaceSignature cspace,
int *len,
char **inknames
) {
	switch(cspace) {
		case icSigCmyData:
			return 0xffff;
			if (inknames != NULL) {
				*inknames = "cyan\000magenta\000yellow\000\000";
				*len = zzstrlen(*inknames);
			}
			return 0;
		case icSigCmykData:
			if (inknames != NULL) {
				*inknames = NULL;
				*len = 0;
			}
			return INKSET_CMYK;

		case icSigGrayData:
		case icSigRgbData:
		case icSigYCbCrData:
		case icSigLabData:
		case icSigXYZData:
		case icSigLuvData:
		case icSigYxyData:
		case icSigHsvData:
		case icSigHlsData:
		case icSig2colorData:
		case icSig3colorData:
		case icSig4colorData:
		case icSig5colorData:
		case icSigMch5Data:
			return 0xffff;

		case icSig6colorData:
		case icSigMch6Data:


			if (inknames != NULL) {
				*inknames = "cyan\000magenta\000yellow\000black\000orange\000green\000\000";
				*len = zzstrlen(*inknames);
			}
			return INKSET_MULTIINK;

		case icSig7colorData:
		case icSigMch7Data:
			return 0xffff;

		case icSig8colorData:
		case icSigMch8Data:


			if (inknames != NULL) {
				*inknames = "cyan\000magenta\000yellow\000black\000orange\000green\000lightcyan\000lightmagenta\000\000";
				*len = zzstrlen(*inknames);
			}
			return INKSET_MULTIINK;
		case icSig9colorData:
		case icSig10colorData:
		case icSig11colorData:
		case icSig12colorData:
		case icSig13colorData:
		case icSig14colorData:
		case icSig15colorData:
		default:
			return 0xffff;
	}
	return 0xffff;
}
