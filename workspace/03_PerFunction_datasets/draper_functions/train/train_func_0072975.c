IoMap_readFromStream_(IoMap *self, BStream *stream)
{
	PHash *hash = DATA(self);

	for (;;)
	{
		int k, v;

		k = BStream_readTaggedInt32(stream);

		if (k == 0)
		{
			break;
		}

		v = BStream_readTaggedInt32(stream);
		PHash_at_put_(hash, IoState_objectWithPid_(IOSTATE, k), IoState_objectWithPid_(IOSTATE, v));
	}
}
