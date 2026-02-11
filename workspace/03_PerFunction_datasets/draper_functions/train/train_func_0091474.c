crypto_sign_encode(SIGNATURE *sig, uint8_t *dest, uint32_t *length)
{
   if (*length == 0) {
      *length = i2d_SignatureData(sig->sigData, NULL);
      return true;
   }

   *length = i2d_SignatureData(sig->sigData, (unsigned char **)&dest);
   return true;
}
