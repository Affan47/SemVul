test1(int argc, char **argv) {
  const char *fname;
  GWEN_BUFFER *rbuf;
  EB_MSG *m;


  if (argc<3) {
    fprintf(stderr, "File name missing.\n");
    return 1;
  }
  fname=argv[2];


  xmlInitParser();
  LIBXML_TEST_VERSION


  if(xmlSecInit() < 0) {
      fprintf(stderr, "Error: xmlsec initialization failed.\n");
      return(-1);
  }


  if(xmlSecCheckVersion() != 1) {
      fprintf(stderr, "Error: loaded xmlsec library version is not compatible.\n");
      return(-1);
  }


#ifdef XMLSEC_CRYPTO_DYNAMIC_LOADING
  if(xmlSecCryptoDLLoadLibrary(BAD_CAST XMLSEC_CRYPTO) < 0) {
      fprintf(stderr, "Error: unable to load default xmlsec-crypto library. Make sure\n"
                      "that you have it installed and check shared libraries path\n"
                      "(LD_LIBRARY_PATH) envornment variable.\n");
      return(-1);
  }
#endif


  if(xmlSecCryptoAppInit(NULL) < 0) {
      fprintf(stderr, "Error: crypto initialization failed.\n");
      return(-1);
  }


  if(xmlSecCryptoInit() < 0) {
      fprintf(stderr, "Error: xmlsec-crypto initialization failed.\n");
      return(-1);
  }

  m=EB_Msg_fromFile(fname);
  if (!m) {
    fprintf(stderr, "Bad file.\n");
    return 3;
  }
  rbuf=GWEN_Buffer_new(0, 256, 0, 1);
  EB_Msg_BuildHashSha1(m, rbuf);

  GWEN_Buffer_Dump(rbuf, 2);

  return 0;
}
