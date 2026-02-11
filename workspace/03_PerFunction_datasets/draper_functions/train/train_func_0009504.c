GetDataHere(void* buf) const {

    char* bufptr = (char*) buf;
    std::list<std::string>::const_reverse_iterator it;

    *((wxUint32*) bufptr) = wxUINT32_SWAP_ON_BE((wxUint32) msccdata.size());
    bufptr += 4;


    for(it = msccdata.rbegin(); it != msccdata.rend(); ++it) {
        *((wxUint16*) bufptr) = wxUINT16_SWAP_ON_BE((wxUint16) it->size());
        bufptr += 2;
        *((wxUint32*) bufptr) = 0;
        bufptr += 4;
    }

    for(it = msccdata.rbegin(); it != msccdata.rend(); ++it) {
        std::memcpy(bufptr, it->data(), it->size());
        bufptr += it->size();
    }
    return true;
}
