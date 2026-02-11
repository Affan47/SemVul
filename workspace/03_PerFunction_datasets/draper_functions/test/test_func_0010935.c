InflateData(const std::string& data) {
    unsigned long len;
    char *out;
    len = data.length();
    out = (char*)(malloc(len * 10));
    z_stream stream;

    stream.zalloc = NULL;
    stream.zfree = NULL;
    stream.opaque = NULL;

    stream.avail_in = len;
    stream.next_in = (Bytef*)(data.c_str());
    stream.total_in = 0;
    stream.avail_out = len*10;
    stream.total_out = 0;
    stream.next_out = (Bytef*)out;

    int rc;
    rc = inflateInit2(&stream, -MAX_WBITS);
    if (rc != Z_OK) {
      std::cerr<<"inflateInit failed"<<std::endl;
      free(out);
      return std::string();
    }

    rc = inflate(&stream, Z_FINISH);
    if (rc != Z_STREAM_END) {
      std::cerr<<"Failed to inflate"<<std::endl;
      inflateEnd(&stream);
      free(out);
      return std::string();
    }
    out[stream.total_out] = 0;
    inflateEnd(&stream);

    std::string ret;
    ret.append(out);

    free(out);
    return ret;
  }
