compress(int level) {
#ifndef HAVE_ZLIB
	return false;
#else

	if(level <= 0 || level > 9 || m_freezed) {
		return false;
	}

	uint32_t uncompressedsize = getPayloadLength();

	if(uncompressedsize == 0) {
		return true;
	}

	uint8_t* compressed = (uint8_t*)malloc(uncompressedsize);
	uLongf compressedsize = uncompressedsize;

	if(compressed == NULL) {
		return NULL;
	}

	if(::compress2(compressed, &compressedsize, getPayload(), uncompressedsize, level) != Z_OK) {
		free(compressed);
		return false;
	}

	clear();
	uint8_t* data = reserve(compressedsize);

	if(data == NULL) {
		free(compressed);
		return false;
	}

	memcpy(data, compressed, compressedsize);
	free(compressed);

	m_freezed = false;
	writePacket<uint32_t>(UncompressedPayloadLengthPos, htobe32(uncompressedsize));
	freeze();

	return true;
#endif
}
