initHistogramsUInt32(
		uint32_t kRadixBits,
		uint32_t kHistBuckets,
		uint32_t kHistSize,
		uint32_t * restrict hist,
		const uint32_t * restrict keysIn,
		uint32_t size)
{
	const uint32_t kHistMask = kHistSize - 1;
	for (uint32_t i = 0; i < size; ++i)
	{
		const uint32_t key = keysIn[i];
		for (uint32_t bucket = 0; bucket < kHistBuckets; ++bucket)
		{
			const uint32_t shift = bucket * kRadixBits;
			const uint32_t pos = (key >> shift) & kHistMask;
			uint32_t * offset = hist + (bucket * kHistSize);
			++offset[pos];
		}
	}
}
