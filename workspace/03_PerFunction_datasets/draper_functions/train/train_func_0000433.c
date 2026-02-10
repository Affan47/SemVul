ADDR_SIZE_AFFECT(_DecodeType dt, _iflags totalPrefixes)
{

	if (totalPrefixes & INST_PRE_ADDR_SIZE) {
		switch (dt)
		{
			case Decode16Bits:
				dt = Decode32Bits;
			break;
			case Decode32Bits:
				dt = Decode16Bits;
			break;
			case Decode64Bits:
				dt = Decode32Bits;
			break;
		}
	}

	return dt;
}
