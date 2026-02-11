OpenObjectFileContainingPcAndGetStartAddress(uint64_t pc,
                                             uint64_t &start_address) {
  int object_fd;


  int maps_fd;
  NO_INTR(maps_fd = open("/proc/self/maps", O_RDONLY));
  FileDescriptor wrapped_maps_fd(maps_fd);
  if (wrapped_maps_fd.get() < 0) {
    return -1;
  }


  char buf[1024];
  LineReader reader(wrapped_maps_fd.get(), buf, sizeof(buf));
  while (true) {
    const char *cursor;
    const char *eol;
    if (!reader.ReadLine(&cursor, &eol)) {
      return -1;
    }


    cursor = GetHex(cursor, eol, &start_address);
    if (cursor == eol || *cursor != '-') {
      return -1;
    }
    ++cursor;


    uint64_t end_address;
    cursor = GetHex(cursor, eol, &end_address);
    if (cursor == eol || *cursor != ' ') {
      return -1;
    }
    ++cursor;


    if (!(start_address <= pc && pc < end_address)) {
      continue;
    }


    const char * const flags_start = cursor;
    while (cursor < eol && *cursor != ' ') {
      ++cursor;
    }

    if (cursor == eol || cursor < flags_start + 4) {
      return -1;
    }


    if (memcmp(flags_start, "r-x", 3) != 0) {
      continue;
    }
    ++cursor;


    int num_spaces = 0;
    while (cursor < eol) {
      if (*cursor == ' ') {
        ++num_spaces;
      } else if (num_spaces >= 3) {


        break;
      }
      ++cursor;
    }
    if (cursor == eol) {
      return -1;
    }


    NO_INTR(object_fd = open(cursor, O_RDONLY));
    if (object_fd < 0) {
      return -1;
    }
    return object_fd;
  }
}
