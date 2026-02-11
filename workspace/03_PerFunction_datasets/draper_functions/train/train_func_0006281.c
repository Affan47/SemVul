compressStringData(const string text, const string filename) {
    if (Log::enabledDbg()) {
        stringstream ss;
        ss << text.size();
        Log::dbg("Compressing content of string with length: " + ss.str());
    }
    std::stringstream compressed ("");
    int ret;
    unsigned have;
    z_stream strm;
    char out[CHUNK];


    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 31, 8, Z_DEFAULT_STRATEGY);
    if (ret != Z_OK) {
         Log::err("zLib Initialization failed at deflateInit2()");
         return "";
    }

    strm.avail_in = text.length();
    strm.next_in = (Bytef*) text.c_str();


    do {
        strm.avail_out = CHUNK;
        strm.next_out = (Bytef*) out;
        ret = deflate(&strm, Z_FINISH);
        have = CHUNK - strm.avail_out;
        compressed.write(out, have);
        if (compressed.bad()) {
            (void)deflateEnd(&strm);
            Log::err("compressStringData error during compression and writing to output buffer");
            return "";
        }
    } while (strm.avail_out == 0);


    (void)deflateEnd(&strm);

    std::stringstream outstream;
    outstream << "begin-base64 644 " << filename << endl;
    encodeBase64(&compressed,&outstream, 76);
    outstream << endl << "====" << endl;

    return outstream.str();
}
