OpenGIF ( LFA_FileRef fileRef, BlockState & inOutBlockState )
	{
		XMP_Uns64 pos = 0;
		unsigned char name;
		XMP_Uns32 len;
		BlockData newBlock;

		pos = LFA_Seek ( fileRef, 0, SEEK_SET );

		pos = ReadHeader ( fileRef );
		if (pos < 13) return 0;

		newBlock.pos = 0;
		newBlock.len = pos;
		newBlock.type = bHeader;
		inOutBlockState.blocks.push_back(newBlock);


		while ( ReadBlock ( fileRef, inOutBlockState, &name, &len, pos) ) {}

		return inOutBlockState.blocks.size();

	}
