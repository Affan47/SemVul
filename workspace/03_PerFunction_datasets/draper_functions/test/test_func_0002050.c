parseExtTimestamp(const char *buffer, int size, bool islocal,
			ParseFileInfo &pfi) {
  if (size < 1) {
    kDebug(7040) << "premature end of extended timestamp (#1)";
    return false;
  }
  int flags = *buffer;
  buffer += 1;
  size -= 1;

  if (flags & 1) {
    if (size < 4) {
      kDebug(7040) << "premature end of extended timestamp (#2)";
      return false;
    }
    pfi.mtime = time_t((uchar)buffer[0] | (uchar)buffer[1] << 8
    			| (uchar)buffer[2] << 16 | (uchar)buffer[3] << 24);
    buffer += 4;
    size -= 4;
  }


  if (!islocal) {
    pfi.exttimestamp_seen = true;
    return true;
  }

  if (flags & 2) {
    if (size < 4) {
      kDebug(7040) << "premature end of extended timestamp (#3)";
      return true;
    }
    pfi.atime = time_t((uchar)buffer[0] | (uchar)buffer[1] << 8
    			| (uchar)buffer[2] << 16 | (uchar)buffer[3] << 24);
    buffer += 4;
    size -= 4;
  }

  if (flags & 4) {
    if (size < 4) {
      kDebug(7040) << "premature end of extended timestamp (#4)";
      return true;
    }
    pfi.ctime = time_t((uchar)buffer[0] | (uchar)buffer[1] << 8
    			| (uchar)buffer[2] << 16 | (uchar)buffer[3] << 24);
    buffer += 4;
  }

  pfi.exttimestamp_seen = true;
  return true;
}
