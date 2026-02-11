getNextTag(char** xmlPtr) {
	char* xml;
	char* tagEnd;
	char* curChar;
	Tag* tag;
	int tagDepth;

	xml = *xmlPtr;
	xml = strchr(xml, '<');

	if(xml == NULL) {
		return NULL;
	}

	tag = (Tag*) malloc(sizeof(Tag));

	tagEnd = strchr(xml, '>');
	tag->name = (char*) malloc(sizeof(char) * (tagEnd -  xml));
	memcpy(tag->name, xml + 1, tagEnd -  xml - 1);
	tag->name[tagEnd -  xml - 1] = '\0';
	if((tagEnd -  xml - 1) > 0) {
		if(tag->name[tagEnd -  xml - 2] == '/') {
			tag->xml = malloc(sizeof(char) * 1);
			tag->xml[0] = '\0';
			*xmlPtr = tagEnd + 1;
			return tag;
		}
	}

	xml = tagEnd;
	curChar = xml;
	tagDepth = 1;
	while(*curChar != '\0') {
		if(*curChar == '<') {
			if(*(curChar + 1) == '/') {
				tagDepth--;
				if(tagDepth == 0) {
					break;
				}
			} else {
				tagDepth++;
			}
		} else if(*curChar == '>') {
			if(*(curChar - 1) == '/') {
				tagDepth--;
			}
		}
		curChar++;
	}

	tag->xml = (char*) malloc(sizeof(char) * (curChar -  xml));
	memcpy(tag->xml, xml + 1, curChar -  xml - 1);
	tag->xml[curChar -  xml - 1] = '\0';

	*xmlPtr = strchr(curChar, '>') + 1;

	return tag;
}
