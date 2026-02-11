oauth_body_hash_file(char *filename) {
  unsigned char fb[BUFSIZ];
  EVP_MD_CTX ctx;
  size_t len=0;
  unsigned char *md;
  FILE *F= fopen(filename, "r");
  if (!F) return NULL;

  EVP_MD_CTX_init(&ctx);
  EVP_DigestInit(&ctx,EVP_sha1());
  while (!feof(F) && (len=fread(fb,sizeof(char),BUFSIZ, F))>0) {
    EVP_DigestUpdate(&ctx, fb, len);
  }
  fclose(F);
  len=0;
  md=(unsigned char*) xcalloc(EVP_MD_size(EVP_sha1()),sizeof(unsigned char));
  EVP_DigestFinal(&ctx, md,(unsigned int*) &len);
  EVP_MD_CTX_cleanup(&ctx);
  return oauth_body_hash_encode(len, md);
}
