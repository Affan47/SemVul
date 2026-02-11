ComputeMessageRepresentative(RandomNumberGenerator &rng,
	const byte *recoverableMessage, size_t recoverableMessageLength,
	HashTransformation &hash, HashIdentifier hashIdentifier, bool messageEmpty,
	byte *representative, size_t representativeBitLength) const
{
	assert(recoverableMessageLength == 0);
	assert(hashIdentifier.second == 0);
	const size_t representativeByteLength = BitsToBytes(representativeBitLength);
	const size_t digestSize = hash.DigestSize();
	const size_t paddingLength = SaturatingSubtract(representativeByteLength, digestSize);

	memset(representative, 0, paddingLength);
	hash.TruncatedFinal(representative+paddingLength, STDMIN(representativeByteLength, digestSize));

	if (digestSize*8 >= representativeBitLength)
	{
		Integer h(representative, representativeByteLength);
		h >>= representativeByteLength*8 - representativeBitLength + 1;
		h.Encode(representative, representativeByteLength);
	}
}
