decodeMetaData(boost::uint8_t *buf, size_t size)
{

    AMF amf;
    boost::uint8_t *ptr = buf;
    boost::uint8_t *tooFar = ptr + size;


    if (*ptr == Element::STRING_AMF0) {
	ptr++;
    }

    boost::uint16_t length;
    length = ntohs((*(boost::uint16_t *)ptr) & 0xffff);
    if (length >= SANE_STR_SIZE) {
	log_error(_("%d bytes for a string is over the safe limit of %d"),
		  length, SANE_STR_SIZE);
    }
    ptr += sizeof(boost::uint16_t);
    std::string name(reinterpret_cast<const char *>(ptr), length);
    ptr += length;


    _metadata = amf.extractAMF(ptr, tooFar);
    if (_metadata.get()) {
    	ptr += amf.totalsize();
	    _metadata->setName(name.c_str(), length);
    }

    return _metadata;
}
