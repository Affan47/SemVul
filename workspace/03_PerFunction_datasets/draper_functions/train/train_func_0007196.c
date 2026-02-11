store_size_info(FIBITMAP *dib, JDIMENSION width, JDIMENSION height) {
	char buffer[256];

	FITAG *tag = FreeImage_CreateTag();
	if(tag) {
		size_t length = 0;

		sprintf(buffer, "%d", (int)width);
		length = strlen(buffer) + 1;
		FreeImage_SetTagKey(tag, "OriginalJPEGWidth");
		FreeImage_SetTagLength(tag, (DWORD)length);
		FreeImage_SetTagCount(tag, (DWORD)length);
		FreeImage_SetTagType(tag, FIDT_ASCII);
		FreeImage_SetTagValue(tag, buffer);
		FreeImage_SetMetadata(FIMD_COMMENTS, dib, FreeImage_GetTagKey(tag), tag);

		sprintf(buffer, "%d", (int)height);
		length = strlen(buffer) + 1;
		FreeImage_SetTagKey(tag, "OriginalJPEGHeight");
		FreeImage_SetTagLength(tag, (DWORD)length);
		FreeImage_SetTagCount(tag, (DWORD)length);
		FreeImage_SetTagType(tag, FIDT_ASCII);
		FreeImage_SetTagValue(tag, buffer);
		FreeImage_SetMetadata(FIMD_COMMENTS, dib, FreeImage_GetTagKey(tag), tag);

		FreeImage_DeleteTag(tag);
	}
}
