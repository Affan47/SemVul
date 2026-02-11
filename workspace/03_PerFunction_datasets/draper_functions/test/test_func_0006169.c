SanitizeOptions(const std::string& dbname,
                        const InternalKeyComparator* icmp,
                        const Options& src) {
  Options result = src;
  result.comparator = icmp;
  ClipToRange(&result.max_open_files,           20,     50000);
  ClipToRange(&result.write_buffer_size,        64<<10, 1<<30);
  ClipToRange(&result.block_size,               1<<10,  4<<20);
  if (result.info_log == NULL) {

    src.env->CreateDir(dbname);
    src.env->RenameFile(InfoLogFileName(dbname), OldInfoLogFileName(dbname));
    Status s = src.env->NewLogger(InfoLogFileName(dbname), &result.info_log);
    if (!s.ok()) {

      result.info_log = NULL;
    }
  }
  if (result.block_cache == NULL) {
    result.block_cache = NewLRUCache(8 << 20);
  }
  return result;
}
