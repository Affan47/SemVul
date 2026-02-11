filenames_are_case_sensitive(void){
  static int caseSensitive;
  static int once = 1;

  if( once ){
    once = 0;
    if( zCaseSensitive ){
      caseSensitive = is_truth(zCaseSensitive);
    }else{
#if defined(_WIN32) || defined(__DARWIN__) || defined(__APPLE__)
      caseSensitive = 0;
#elif defined(__CYGWIN__)

      void *hKey;
      int value = 1, length = sizeof(int);
      caseSensitive = 0;
      if( (RegOpenKeyExW((void *)0x80000002, L"SYSTEM\\CurrentControlSet\\"
          "Control\\Session Manager\\kernel", 0, 1, (void *)&hKey)
          == 0) && (RegQueryValueExW(hKey, L"obcaseinsensitive",
          0, NULL, (void *)&value, (void *)&length) == 0) && !value ){
        caseSensitive = 1;
      }
#else
      caseSensitive = 1;
#endif
      caseSensitive = db_get_boolean("case-sensitive",caseSensitive);
    }
    if( !caseSensitive && g.localOpen ){
      db_multi_exec(
         "CREATE INDEX IF NOT EXISTS vfile_nocase"
         "  ON vfile(pathname COLLATE nocase)"
      );
    }
  }
  return caseSensitive;
}
