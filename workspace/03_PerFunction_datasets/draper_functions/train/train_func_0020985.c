rfbEnableExtension(rfbClientPtr cl, rfbProtocolExtension* extension,
	void* data)
{
	rfbExtensionData* extData;


	for(extData = cl->extensions; extData; extData = extData->next)
		if(extData->extension == extension)
			return FALSE;

	extData = calloc(sizeof(rfbExtensionData),1);
	extData->extension = extension;
	extData->data = data;
	extData->next = cl->extensions;
	cl->extensions = extData;

	return TRUE;
}
