read_block(Bit8u* buf, Bit32u lba, int blocksize)
{


#ifdef WIN32
  LARGE_INTEGER pos;
#else
  off_t pos;
#endif
  ssize_t n = 0;
  Bit8u try_count = 3;
  Bit8u* buf1;

  if (blocksize == 2352) {
    memset(buf, 0, 2352);
    memset(buf+1, 0xff, 10);
    Bit32u raw_block = lba + 150;
    buf[12] = (raw_block / 75) / 60;
    buf[13] = (raw_block / 75) % 60;
    buf[14] = (raw_block % 75);
    buf[15] = 0x01;
    buf1 = buf + 16;
  } else {
    buf1 = buf;
  }
  do {
#ifdef WIN32
    if(bUseASPI) {
      ReadCDSector(hid, tid, lun, lba, buf1, BX_CD_FRAMESIZE);
      n = BX_CD_FRAMESIZE;
    } else {
      pos.QuadPart = (LONGLONG)lba*BX_CD_FRAMESIZE;
      pos.LowPart = SetFilePointer(hFile, pos.LowPart, &pos.HighPart, SEEK_SET);
      if ((pos.LowPart == 0xffffffff) && (GetLastError() != NO_ERROR)) {
        BX_PANIC(("cdrom: read_block: SetFilePointer returned error."));
      } else {
        ReadFile(hFile, (void *) buf1, BX_CD_FRAMESIZE, (unsigned long *) &n, NULL);
      }
    }
#elif defined(__APPLE__)
#define CD_SEEK_DISTANCE kCDSectorSizeWhole
    if(using_file)
    {
      pos = lseek(fd, (off_t) lba * BX_CD_FRAMESIZE, SEEK_SET);
      if (pos < 0) {
        BX_PANIC(("cdrom: read_block: lseek returned error."));
      } else {
        n = read(fd, buf1, BX_CD_FRAMESIZE);
      }
    }
    else
    {


      pos = lseek(fd, (off_t) lba * CD_SEEK_DISTANCE + 16, SEEK_SET);
      if (pos < 0) {
        BX_PANIC(("cdrom: read_block: lseek returned error."));
      } else {
        n = read(fd, buf1, CD_FRAMESIZE);
      }
    }
#else
    pos = lseek(fd, (off_t) lba * BX_CD_FRAMESIZE, SEEK_SET);
    if (pos < 0) {
      BX_PANIC(("cdrom: read_block: lseek returned error."));
    } else {
      n = read(fd, (char*) buf1, BX_CD_FRAMESIZE);
    }
#endif
  } while ((n != BX_CD_FRAMESIZE) && (--try_count > 0));

  return (n == BX_CD_FRAMESIZE);
}
