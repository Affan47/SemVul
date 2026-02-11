des_ecb_crypt (struct _des_ctx *ctx, const byte * from, byte * to, int mode)
{
  u32 left, right, work;
  u32 *keys;

  keys = mode ? ctx->decrypt_subkeys : ctx->encrypt_subkeys;

  READ_64BIT_DATA (from, left, right)
  INITIAL_PERMUTATION (left, work, right)

  DES_ROUND (right, left, work, keys) DES_ROUND (left, right, work, keys)
  DES_ROUND (right, left, work, keys) DES_ROUND (left, right, work, keys)
  DES_ROUND (right, left, work, keys) DES_ROUND (left, right, work, keys)
  DES_ROUND (right, left, work, keys) DES_ROUND (left, right, work, keys)
  DES_ROUND (right, left, work, keys) DES_ROUND (left, right, work, keys)
  DES_ROUND (right, left, work, keys) DES_ROUND (left, right, work, keys)
  DES_ROUND (right, left, work, keys) DES_ROUND (left, right, work, keys)
  DES_ROUND (right, left, work, keys) DES_ROUND (left, right, work, keys)

  FINAL_PERMUTATION (right, work, left)
  WRITE_64BIT_DATA (to, right, left)

  return 0;
}
