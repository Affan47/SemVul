NMEPluginTOC(NMEConstText name, NMEInt nameLen,
		NMEConstText data, NMEInt dataLen,
		NMEContext *context,
		void *userData)
{
	char *endp;
	HookTOCData hookData;
	NMEText title, buf, dest;
	NMEInt titleLen, bufLen, destLen;
	NMEOutputFormat outputFormat;
	NMEInt options, fontSize;
	NMEErr err;
	(void)name;
	(void)nameLen;

	NMESetTOCOutputFormat(&outputFormat, &hookData);


	hookData.level1 = strtol(data, &endp, 0);
	hookData.level2 = strtol(endp, &endp, 0);
	if (hookData.level1 < 1)
		return kNMEErrOk;
	if (hookData.level2 < hookData.level1)
		hookData.level2 = hookData.level1;


	for (title = endp; title < data + dataLen && isBlankOrEol(title[0]); title++)
		;
	for (titleLen = dataLen - (title - data);
			titleLen > 0 && isBlankOrEol(title[titleLen - 1]);
			titleLen--)
		;


	NMEGetTempMemory(context, &buf, &bufLen);
	NMEGetFormat(context, NULL, &options, &fontSize);
	err = NMEProcess(((NMEPluginTocData *)userData)->src,
			((NMEPluginTocData *)userData)->srcLen,
			buf, bufLen,
			options | kNMEProcessOptNoPreAndPost, "\n", &outputFormat, fontSize,
			&dest, &destLen, NULL);
	if (err != kNMEErrOk)
		return err;


	if (titleLen > 0)
		if (!NMEAddString("<h2%%{s>0} style=\"font-size:%{2*s}pt\"%%>", -1, '%', context)
				|| !NMEAddString(title, titleLen, '\0', context)
				|| !NMEAddString("</h2>\n", -1, '%', context))
			return kNMEErrNotEnoughMemory;


	if (!NMEAddString("<p%%{s>0} style=\"font-size:%{s}pt\"%%>\n", -1, '%', context)
			|| !NMEAddString(dest, destLen, '\0', context)
			|| !NMEAddString("</p>\n", -1, '%', context))
		return kNMEErrNotEnoughMemory;

	return kNMEErrOk;
}
