resetDatabaseReferenceTime()
{


#ifdef HAVE_DECLARATION_STRUCT_UTIMBUF
    struct utimbuf utime_buf;
    utime_buf.actime  = OFstatic_cast(time_t, referenceTime);
    utime_buf.modtime = OFstatic_cast(time_t, referenceTime);
    if (0 != utime(databaseIndexFile.c_str(), &utime_buf))
#else

    time_t utime_buf[2];
    utime_buf[0]  = OFstatic_cast(time_t, referenceTime);
    utime_buf[1] = OFstatic_cast(time_t, referenceTime);
    if (0 != utime(OFconst_cast(char *, databaseIndexFile.c_str()), utime_buf))
#endif
    {
      DCMPSTAT_WARN("Cannot set database index file modification time");
    } else {
      struct stat stat_buf;
      if (0 == stat(databaseIndexFile.c_str(), &stat_buf))
      {
        referenceTime = OFstatic_cast(unsigned long, stat_buf.st_mtime);
      }
    }
}
