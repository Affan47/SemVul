CheckTag ( IO::InputStream* inputStream, TagState& inOutTagState, TagData& inOutTagData )
	{
		unsigned long ret = 0;
		XMP_Uns8 * buffer = 0;

		try {

			if ( inOutTagData.id == SWF_TAG_ID_METADATA ) {

				buffer = new XMP_Uns8[inOutTagData.len];
				XMP_Uns32 bytes = inputStream->Read ( buffer, inOutTagData.len );

				XMP_Assert ( bytes == inOutTagData.len );

				inOutTagState.xmpPos = inOutTagData.pos + inOutTagData.offset;
				inOutTagState.xmpLen = inOutTagData.len;
				inOutTagData.xmp = true;

				inOutTagState.xmpPacket.assign ( (char*)buffer, inOutTagData.len );

				delete[] buffer;
				buffer = 0;
				ret = inOutTagState.xmpLen;

			}

		} catch ( ... ) {

			if ( buffer != 0 ) {
				delete[] buffer;
				buffer = 0;
			}

		}

		if ( buffer != 0 ) {
			delete[] buffer;
			buffer = 0;
		}

		return ret;

	}
