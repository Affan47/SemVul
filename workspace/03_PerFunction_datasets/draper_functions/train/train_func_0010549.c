getImageDecoder (const std::string& strFile)
{
	std::string strExt = extension(strFile);
#ifdef RETIN_ENABLE_PNG
	if (strExt == ".png")
		return new ImageDecoderPNG();
#endif
#ifdef RETIN_ENABLE_JPEG
	if (strExt == ".jpeg" || strExt == ".jpg")
		return new ImageDecoderJPEG();
#endif
#ifdef RETIN_ENABLE_PBM
        if (strExt == ".pgm")
                return new ImageDecoderPBM();
#endif
	return NULL;

}
