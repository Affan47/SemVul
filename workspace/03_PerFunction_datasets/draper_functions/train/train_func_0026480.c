rijndael_encrypt(RIJNDAEL_context *ctx,
		 const UINT8 *plaintext,
		 UINT8 *ciphertext)
{
  int r, j;
  UINT32 wtxt[4], t[4];
  UINT32 e;

  key_addition_8to32(plaintext, &(ctx->keys[0]), wtxt);
  for (r=1; r<ctx->nrounds; r++) {
    for (j=0; j<4; j++) {
      t[j] = dtbl[wtxt[j] & 0xff] ^
	ROTRBYTE(dtbl[(wtxt[idx[1][j]] >> 8) & 0xff]^
		 ROTRBYTE(dtbl[(wtxt[idx[2][j]] >> 16) & 0xff] ^
			  ROTRBYTE(dtbl[(wtxt[idx[3][j]] >> 24) & 0xff])));
    }
    key_addition32(t, &(ctx->keys[r*4]), wtxt);
  }


  for (j=0; j<4; j++) {
    e = wtxt[j] & 0xff;
    e |= (wtxt[idx[1][j]]) & (0xff  << 8 );
    e |= (wtxt[idx[2][j]]) & (0xff  << 16);
    e |= (wtxt[idx[3][j]]) & (0xffU << 24);
    t[j] = e;
  }
  for (j=0; j<4; j++)
    t[j] = SUBBYTE(t[j], sbox);
  key_addition32to8(t, &(ctx->keys[4*ctx->nrounds]), ciphertext);
}
