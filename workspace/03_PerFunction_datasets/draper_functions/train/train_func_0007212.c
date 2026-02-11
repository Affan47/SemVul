FreeImage_SetTagValue(FITAG *tag, const void *value) {
	if(tag && value) {
		FITAGHEADER *tag_header = (FITAGHEADER *)tag->data;

		if(tag_header->count * FreeImage_TagDataWidth((FREE_IMAGE_MDTYPE)tag_header->type) != tag_header->length) {

			return FALSE;
		}

		if(tag_header->value) {
			free(tag_header->value);
		}

		switch(tag_header->type) {
			case FIDT_ASCII:
			{
				tag_header->value = (char*)malloc((tag_header->length + 1) * sizeof(char));
				if(!tag_header->value) {
					return FALSE;
				}
				char *src_data = (char*)value;
				char *dst_data = (char*)tag_header->value;
				for(DWORD i = 0; i < tag_header->length; i++) {
					dst_data[i] = src_data[i];
				}
				dst_data[tag_header->length] = '\0';
			}
			break;

			default:
				tag_header->value = malloc(tag_header->length * sizeof(BYTE));
				if(!tag_header->value) {
					return FALSE;
				}
				memcpy(tag_header->value, value, tag_header->length);
				break;
		}
		return TRUE;
	}
	return FALSE;
}
