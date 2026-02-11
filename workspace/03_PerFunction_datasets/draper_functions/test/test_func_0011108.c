PrinfASF_UTF16 (LFA_FileRef file, XMP_Uns16 byteCount, const char * label)
{
	size_t filePos = LFA_Tell (file);

	CaptureFileData (file, 0, byteCount);

	tree->setKeyValue(
		label,
		convert16Bit(false,sDataPtr,false,byteCount),
		fromArgs("offset %d (0x%X), size %d",filePos, filePos, byteCount)
		);
}
