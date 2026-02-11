hmac_sha_md5 (const char *buffer, size_t len, char *key, size_t key_len, char *resbuf, int type) {

  char Ki[SHA512_BLOCKSIZE];
  char Ko[SHA512_BLOCKSIZE];
  char tmpbuf[SHA512_DIGESTSIZE];
  int i;
  int blocksize;
  int digestsize;
  void *ctx;
  void (*init_ctx)(void *);
  void (*process_bytes)(void *, size_t, void *);
  void *(*finish_ctx)(void *, void *);
  void *result;

  switch (type) {
          case 5:
                  ctx = malloc(sizeof(struct md5_ctx));
                  init_ctx      = (void(*)(void *))                 &md5_init_ctx;
                  process_bytes = (void(*)(void *, size_t, void *)) &md5_process_bytes;
                  finish_ctx    = (void* (*)(void *, void *))       &md5_finish_ctx;
                  blocksize = MD5_BLOCKSIZE;
                  digestsize = MD5_DIGESTSIZE;
                  break;


          SHA_CASE(  1,   1)
          SHA_CASE(224, 256)
          SHA_CASE(256, 256)
          SHA_CASE(384, 512)
          SHA_CASE(512, 512)
          default:
                  return NULL;
  }


  if (key_len > blocksize) {
          init_ctx (&ctx);
          process_bytes (key, key_len, &ctx);
          finish_ctx (&ctx, Ki);
          key_len = digestsize;
          memcpy(Ko, Ki, key_len);
  } else {
          memcpy(Ki, key, key_len);
          memcpy(Ko, key, key_len);
  }


  for (i = 0; i < key_len; i++) {
          Ki[i] ^= 0x36;
          Ko[i] ^= 0x5c;
  }
  for (; i < blocksize; i++) {
          Ki[i] = 0x36;
          Ko[i] = 0x5c;
  }

  init_ctx (ctx);
  process_bytes (Ki, blocksize, ctx);
  process_bytes ((void *)buffer, len, ctx);
  finish_ctx (ctx, tmpbuf);

  init_ctx (ctx);
  process_bytes (Ko, blocksize, ctx);
  process_bytes (tmpbuf, digestsize, ctx);

  result = finish_ctx (ctx, resbuf);
  free(ctx);

  return result;
}
