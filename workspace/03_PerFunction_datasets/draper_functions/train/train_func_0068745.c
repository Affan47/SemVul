convert_B8G8R8A8toA8R8G8B8(const void* sP, s32 sN, void* dP)
{
	u8* sB = (u8*)sP;
	u8* dB = (u8*)dP;

	for (s32 x = 0; x < sN; ++x)
	{
		dB[0] = sB[3];
		dB[1] = sB[2];
		dB[2] = sB[1];
		dB[3] = sB[0];

		sB += 4;
		dB += 4;
	}

}
