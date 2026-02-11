matchedFile(uint64 len, const RsyncSum64& r,
                          const MD5Sum& md5) {
    files.reserve((files.size() + 16) % 16);
    files.push_back(new JigdoDesc::MatchedFile(offset, len, r, md5));
    offset += len;
  }
