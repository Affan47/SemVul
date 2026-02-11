parHookTOC(NMEInt level,
		NMEInt item,
		NMEBoolean enter,
		NMEConstText markup,
		NMEInt srcIndex,
		NMEContext *context,
		void *data)
{
	HookTOCData *d = (HookTOCData *)data;

	if (markup[0] == '=' && level >= d->level1 && level <= d->level2)
		switchOutputFormatTOC(d, enter);

	return kNMEErrOk;
}
