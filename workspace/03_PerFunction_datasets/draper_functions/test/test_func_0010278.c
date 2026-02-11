store_password(LEX *lc, RES_ITEM *item, int index, int pass)
{
   unsigned int i, j;
   struct MD5Context md5c;
   unsigned char digest[CRYPTO_DIGEST_MD5_SIZE];
   char sig[100];


   lex_get_token(lc, T_STRING);
   if (pass == 1) {
      MD5Init(&md5c);
      MD5Update(&md5c, (unsigned char *) (lc->str), lc->str_len);
      MD5Final(digest, &md5c);
      for (i = j = 0; i < sizeof(digest); i++) {
         sprintf(&sig[j], "%02x", digest[i]);
         j += 2;
      }
      *(item->value) = bstrdup(sig);
   }
   scan_to_eol(lc);
   set_bit(index, res_all.hdr.item_present);
}
