NMEEncodeCharFunDict(NMEConstText src, NMEInt srcLen, NMEInt *srcIx,
		NMEContext *context, void *data)
{
	NMEInt i;
	(void)srcLen;

	for (i = 0; ((NMEEncodeCharDict const *)data)[i].str; i++)
		if (src[*srcIx] == ((NMEEncodeCharDict const *)data)[i].ch)
		{
			if (!NMEAddString(((NMEEncodeCharDict const *)data)[i].str, -1,
					context->ctrlChar, context))
				return kNMEErrNotEnoughMemory;
			(*srcIx)++;
			return kNMEErrOk;
		}
	if (!NMEAddString(&src[(*srcIx)++], 1, context->ctrlChar, context))
		return kNMEErrNotEnoughMemory;
	return kNMEErrOk;
}
