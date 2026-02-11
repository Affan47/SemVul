NMEPluginRot13(NMEConstText name, NMEInt nameLen,
		NMEConstText data, NMEInt dataLen,
		NMEContext *context,
		void *userData)
{
	NMEInt i;
	NMEChar c;
	(void)name;
	(void)nameLen;
	(void)userData;

	for (i = 0; i < dataLen; i++)
	{
		c = (data[i] | 32) >= 'a' && (data[i] | 32) <= 'm'
				? data[i] + 13
				: (data[i] | 32) >= 'n' && (data[i] | 32) <= 'z'
				? data[i] - 13
				: data[i];
		if (!NMEAddString(&c, 1, '\0', context))
			return kNMEErrNotEnoughMemory;
	}

	return kNMEErrOk;
}
