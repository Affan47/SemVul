ReadHeader(unsigned long fPos) {
      #if DEBUG
      std::cout << "List::Readheader(ulong) ";
      #endif
        Chunk::ReadHeader(fPos);
        if (CurrentChunkSize < 4) return;
        NewChunkSize = CurrentChunkSize -= 4;
        #if POSIX
        lseek(pFile->hFileRead, fPos + CHUNK_HEADER_SIZE, SEEK_SET);
        read(pFile->hFileRead, &ListType, 4);
        #elif defined(WIN32)
        SetFilePointer(pFile->hFileRead, fPos + CHUNK_HEADER_SIZE, NULL, FILE_BEGIN);
        DWORD dwBytesRead;
        ReadFile(pFile->hFileRead, &ListType, 4, &dwBytesRead, NULL);
        #else
        fseek(pFile->hFileRead, fPos + CHUNK_HEADER_SIZE, SEEK_SET);
        fread(&ListType, 4, 1, pFile->hFileRead);
        #endif
      #if DEBUG
      std::cout << "listType=" << convertToString(ListType) << std::endl;
      #endif
        if (!pFile->bEndianNative) {

        }
    }
