ColorSpaceSignature2TiffPhotometric(
icColorSpaceSignature cspace
) {
	switch(cspace) {
		case icSigGrayData:
			return PHOTOMETRIC_MINISBLACK;
		case icSigRgbData:
			return PHOTOMETRIC_RGB;
		case icSigCmykData:
			return PHOTOMETRIC_SEPARATED;
		case icSigYCbCrData:
			return PHOTOMETRIC_YCBCR;
		case icSigLabData:
			return PHOTOMETRIC_CIELAB;

		case icSigXYZData:
		case icSigLuvData:
		case icSigYxyData:
		case icSigHsvData:
		case icSigHlsData:
		case icSigCmyData:
		case icSig2colorData:
		case icSig3colorData:
		case icSig4colorData:
		case icSig5colorData:
		case icSigMch5Data:
		case icSig6colorData:
		case icSigMch6Data:
		case icSig7colorData:
		case icSigMch7Data:
		case icSig8colorData:
		case icSigMch8Data:
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
