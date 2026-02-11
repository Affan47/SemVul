checksum(FXString & io){
  if (io.empty()) return;
#ifdef HAVE_GCRYPT
  FXuchar digest[16];
  gcry_md_hash_buffer(GCRY_MD_MD5,(void*)digest,(const void*)io.text(),io.length());
#else
  md5_state_t pms;
  md5_byte_t digest[16];
  md5_init(&pms);
  md5_append(&pms,(const md5_byte_t*)io.text(),io.length());
  md5_finish(&pms,digest);
#endif

  io.length(32);
#if FOXVERSION < FXVERSION(1,7,0)
  for (FXint i=0,d=0;i<32;i+=2,d++) {
    io[i]=FXString::hex[(digest[d]/16)%16];
    io[i+1]=FXString::hex[digest[d]%16];
    }
#else
  for (FXint i=0,d=0;i<32;i+=2,d++) {
    io[i]=Ascii::toLower(FXString::value2Digit[(digest[d]/16)%16]);
    io[i+1]=Ascii::toLower(FXString::value2Digit[digest[d]%16]);
    }
#endif
  }
