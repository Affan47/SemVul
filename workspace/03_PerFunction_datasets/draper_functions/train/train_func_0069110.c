process_header(struct poet_ctx *ctx, const uint8_t  *header,
		    uint64_t header_len )
{
  block mask;
  block factor;
  block in;
  block out;
  block product;
  uint64_t offset=0;

  ctx->mlen=0;
  memset(factor,0,BLOCKLEN);
  memset(product,0,BLOCKLEN);
  memset(mask,0,BLOCKLEN);
  memset(ctx->tau,0,BLOCKLEN);

  product[0] = 0x80;
  factor[0]  = 0x40;

  while(header_len > BLOCKLEN)
    {
      gf_mul(mask, product, ctx->l);
      xor_block(in,header+offset,mask);
      AES_encrypt(in,out,&(ctx->aes_enc));
      xor_block(ctx->tau,out,ctx->tau);

      offset += BLOCKLEN;
      header_len -= BLOCKLEN;

      gf_mul(product,product,factor);
    }


  if(header_len < 16)
    {
      factor[0]=0xA0;
      memset(in,0,BLOCKLEN);
      memcpy(in,header+offset,header_len);
      in[header_len]=0x80;
    }
  else
    {
      factor[0]=0xC0;
      memcpy(in,header+offset,BLOCKLEN);
    }

  gf_mul(product,product,factor);
  gf_mul(mask,product,ctx->l);
  xor_block(in,mask,in);

  xor_block(in,in,ctx->tau);
  AES_encrypt(in ,ctx->tau, &(ctx->aes_enc));

  memcpy(ctx->x, ctx->tau, BLOCKLEN);
  memcpy(ctx->y, ctx->tau, BLOCKLEN);
}
