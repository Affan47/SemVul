sequentialNonOverlappingRead(DcmElement *delem, DcmFileCache *dcache, unsigned char *buffer)
{
    unsigned char *target = new unsigned char[BUFSIZE];
    Uint32 offset = 0;
    Uint32 bytes_to_read = 0;
    OFCondition cond;

    while (offset < BUFSIZE)
    {
      bytes_to_read = (rand() % 20)+1;


      if (offset + bytes_to_read > BUFSIZE) bytes_to_read = BUFSIZE - offset;

      cond = delem->getPartialValue(target, offset, bytes_to_read, dcache);
      if (cond.bad())
      {

        delete[] target;
        return cond;
      }

      if (0 != memcmp(target, buffer+offset, bytes_to_read))
      {
        OFOStringStream str;
        str << "Error: unexpected sequence of " << bytes_to_read << " bytes found at offset " << offset << OFendl;
        str << "Expected: ";
        for (Uint32 i=0; i<bytes_to_read; ++i)
        {
          str << STD_NAMESPACE hex << OFstatic_cast(int, buffer[offset+i]) << " ";
        }
        str << OFendl << "Found   : ";
        for (Uint32 j=0; j<bytes_to_read; ++j)
        {
          str << STD_NAMESPACE hex << OFstatic_cast(int, target[j]) << " ";
        }
        str << OFStringStream_ends;

        OFSTRINGSTREAM_GETSTR(str, c_str)
        OFCHECK_FAIL(c_str);
        OFSTRINGSTREAM_FREESTR(c_str)
        delete[] target;
        return EC_IllegalCall;
      }

      offset += bytes_to_read;
    }
    delete[] target;
    return EC_Normal;
}
