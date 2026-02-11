CheckForCorruptedBuffer(const MallocBlockQueueEntry& queue_entry,
                                      size_t buffer_idx,
                                      const unsigned char* buffer,
                                      size_t size_of_buffer) {
    if (memcmp(buffer, kMagicDeletedBuffer, size_of_buffer) == 0) {
      return;
    }

    RAW_LOG(ERROR,
            "Found a corrupted memory buffer in MallocBlock (may be offset "
            "from user ptr): buffer index: %zd, buffer ptr: %p, size of "
            "buffer: %zd", buffer_idx, buffer, size_of_buffer);


    if (size_of_buffer <= 1024) {
      for (int i = 0; i < size_of_buffer; ++i) {
        if (buffer[i] != kMagicDeletedByte) {
          RAW_LOG(ERROR, "Buffer byte %d is 0x%02x (should be 0x%02x).",
                  i, buffer[i], kMagicDeletedByte);
        }
      }
    } else {
      RAW_LOG(ERROR, "Buffer too large to print corruption.");
    }

    const MallocBlock* b = queue_entry.block;
    const size_t size = queue_entry.size;
    if (queue_entry.num_deleter_pcs > 0) {
      TracePrintf(STDERR_FILENO, "Deleted by thread %p\n",
                  reinterpret_cast<void*>(
                      PRINTABLE_PTHREAD(queue_entry.deleter_threadid)));


      union { void* alignment; char buf[sizeof(SymbolTable)]; } tablebuf;
      SymbolTable* symbolization_table = new (tablebuf.buf) SymbolTable;
      for (int i = 0; i < queue_entry.num_deleter_pcs; i++) {


        char *pc = reinterpret_cast<char*>(queue_entry.deleter_pcs[i]);
        symbolization_table->Add(pc - 1);
      }
      if (FLAGS_symbolize_stacktrace)
        symbolization_table->Symbolize();
      for (int i = 0; i < queue_entry.num_deleter_pcs; i++) {
        char *pc = reinterpret_cast<char*>(queue_entry.deleter_pcs[i]);
        TracePrintf(STDERR_FILENO, "    @ %p %s\n",
                    pc, symbolization_table->GetSymbol(pc - 1));
      }
    } else {
      RAW_LOG(ERROR,
              "Skipping the printing of the deleter's stack!  Its stack was "
              "not found; either the corruption occurred too early in "
              "execution to obtain a stack trace or --max_free_queue_size was "
              "set to 0.");
    }

    RAW_LOG(FATAL,
            "Memory was written to after being freed.  MallocBlock: %p, user "
            "ptr: %p, size: %zd.  If you can't find the source of the error, "
            "try using ASan (http://code.google.com/p/address-sanitizer/), "
            "Valgrind, or Purify, or study the "
            "output of the deleter's stack printed above.",
            b, b->data_addr(), size);
  }
