ReadHeaderLength(BgzfStream* stream, uint32_t& length) {


    char buffer[sizeof(uint32_t)];
    if ( stream->Read(buffer, sizeof(uint32_t)) != sizeof(uint32_t) ) {
        fprintf(stderr, "BamHeader ERROR: could not read header length\n");
        return false;
    }


    length = BamTools::UnpackUnsignedInt(buffer);
    if ( BamTools::SystemIsBigEndian() )
        BamTools::SwapEndian_32(length);
    return true;
}
