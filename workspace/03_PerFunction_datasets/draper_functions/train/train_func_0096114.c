findTag(PPPoEPacket *packet, UINT16_t type, PPPoETag *tag)
{
    UINT16_t len = ntohs(packet->length);
    unsigned char *curTag;
    UINT16_t tagType, tagLen;

    if (packet->ver != 1) {
	error("Invalid PPPoE version (%u)", packet->ver);
	return NULL;
    }
    if (packet->type != 1) {
	error("Invalid PPPoE type (%u)", packet->type);
	return NULL;
    }


    if (len > ETH_DATA_LEN - 6) {
	error("Invalid PPPoE packet length (%u)", len);
	return NULL;
    }


    curTag = packet->payload;
    while(curTag - packet->payload < len) {

	tagType = (((UINT16_t) curTag[0]) << 8) +
	    (UINT16_t) curTag[1];
	tagLen = (((UINT16_t) curTag[2]) << 8) +
	    (UINT16_t) curTag[3];
	if (tagType == TAG_END_OF_LIST) {
	    return NULL;
	}
	if ((curTag - packet->payload) + tagLen + TAG_HDR_SIZE > len) {
	    error("Invalid PPPoE tag length (%u)", tagLen);
	    return NULL;
	}
	if (tagType == type) {
	    memcpy(tag, curTag, tagLen + TAG_HDR_SIZE);
	    return curTag;
	}
	curTag = curTag + TAG_HDR_SIZE + tagLen;
    }
    return NULL;
}
