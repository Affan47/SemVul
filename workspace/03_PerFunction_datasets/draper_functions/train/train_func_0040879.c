GetStats(char* buffer, int buffer_length) {
    ASSERT(buffer_length > 0);
    TCMalloc_Printer printer(buffer, buffer_length);


    if (buffer_length < 10000) {
      DumpStats(&printer, 1);
    } else {
      DumpStats(&printer, 2);
    }
  }
