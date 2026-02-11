AdvancedProcessBlocks(const byte *inBlocks, const byte *xorBlocks, byte *outBlocks, size_t length, word32 flags) const
{
#if CRYPTOPP_BOOL_AESNI_INTRINSICS_AVAILABLE
	if (HasAESNI())
		return AESNI_AdvancedProcessBlocks(AESNI_Enc_Block, AESNI_Enc_4_Blocks, (const __m128i *)m_key.begin(), m_rounds, inBlocks, xorBlocks, outBlocks, length, flags);
#endif

#if CRYPTOPP_BOOL_SSE2_ASM_AVAILABLE || defined(CRYPTOPP_X64_MASM_AVAILABLE)
	if (HasSSE2())
	{
		if (length < BLOCKSIZE)
			return length;

		struct Locals
		{
			word32 subkeys[4*12], workspace[8];
			const byte *inBlocks, *inXorBlocks, *outXorBlocks;
			byte *outBlocks;
			size_t inIncrement, inXorIncrement, outXorIncrement, outIncrement;
			size_t regSpill, lengthAndCounterFlag, keysBegin;
		};

		size_t increment = BLOCKSIZE;
		const byte* zeros = (byte *)(Te+256);
		byte *space;

		do {
			space = (byte *)alloca(255+sizeof(Locals));
			space += (256-(size_t)space%256)%256;
		}
		while (AliasedWithTable(space, space+sizeof(Locals)));

		if (flags & BT_ReverseDirection)
		{
			assert(length % BLOCKSIZE == 0);
			inBlocks += length - BLOCKSIZE;
			xorBlocks += length - BLOCKSIZE;
			outBlocks += length - BLOCKSIZE;
			increment = 0-increment;
		}

		Locals &locals = *(Locals *)space;

		locals.inBlocks = inBlocks;
		locals.inXorBlocks = (flags & BT_XorInput) && xorBlocks ? xorBlocks : zeros;
		locals.outXorBlocks = (flags & BT_XorInput) || !xorBlocks ? zeros : xorBlocks;
		locals.outBlocks = outBlocks;

		locals.inIncrement = (flags & BT_DontIncrementInOutPointers) ? 0 : increment;
		locals.inXorIncrement = (flags & BT_XorInput) && xorBlocks ? increment : 0;
		locals.outXorIncrement = (flags & BT_XorInput) || !xorBlocks ? 0 : increment;
		locals.outIncrement = (flags & BT_DontIncrementInOutPointers) ? 0 : increment;

		locals.lengthAndCounterFlag = length - (length%16) - bool(flags & BT_InBlockIsCounter);
		int keysToCopy = m_rounds - (flags & BT_InBlockIsCounter ? 3 : 2);
		locals.keysBegin = (12-keysToCopy)*16;

		Rijndael_Enc_AdvancedProcessBlocks(&locals, m_key);
		return length % BLOCKSIZE;
	}
#endif

	return BlockTransformation::AdvancedProcessBlocks(inBlocks, xorBlocks, outBlocks, length, flags);
}
