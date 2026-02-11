ReadChunk ( LFA_FileRef fileRef, ChunkState & inOutChunkState, long * chunkType, XMP_Uns32 * chunkLength, XMP_Uns64 & inOutPosition )
	{
		try
		{
			XMP_Uns64 startPosition = inOutPosition;
			long bytesRead;
			char buffer[4];

			bytesRead = LFA_Read ( fileRef, buffer, 4 );
			if ( bytesRead != 4 ) return false;
			inOutPosition += 4;
			*chunkLength = GetUns32BE(buffer);

			bytesRead = LFA_Read ( fileRef, buffer, 4 );
			if ( bytesRead != 4 ) return false;
			inOutPosition += 4;
			*chunkType = GetUns32BE(buffer);

			inOutPosition += *chunkLength;

			bytesRead = LFA_Read ( fileRef, buffer, 4 );
			if ( bytesRead != 4 ) return false;
			inOutPosition += 4;
			long crc = GetUns32BE(buffer);

			ChunkData	newChunk;

			newChunk.pos = startPosition;
			newChunk.len = *chunkLength;
			newChunk.type = *chunkType;


			if (newChunk.type == iTXt)
			{
				CheckiTXtChunkHeader(fileRef, inOutChunkState, newChunk);
			}

			inOutChunkState.chunks.push_back ( newChunk );

			LFA_Seek ( fileRef, inOutPosition, SEEK_SET );

		} catch ( ... ) {

			return false;

		}

		return true;

	}
