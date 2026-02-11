EncryptString(char type,char *in,char *out,unsigned char *key,int plainlen)

{ int cipherlen = 0, tmplen;
  unsigned char iv[32] = {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
  EVP_CIPHER_CTX ctx;

EVP_CIPHER_CTX_init(&ctx);
EVP_EncryptInit_ex(&ctx,CfengineCipher(type),NULL,key,iv);

if (!EVP_EncryptUpdate(&ctx,out,&cipherlen,in,plainlen))
   {
   EVP_CIPHER_CTX_cleanup(&ctx);
   return -1;
   }

if (!EVP_EncryptFinal_ex(&ctx,out+cipherlen,&tmplen))
   {
   EVP_CIPHER_CTX_cleanup(&ctx);
   return -1;
   }

cipherlen += tmplen;
EVP_CIPHER_CTX_cleanup(&ctx);
return cipherlen;
}
