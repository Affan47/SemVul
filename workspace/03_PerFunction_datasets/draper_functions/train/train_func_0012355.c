createAlgorithmForPrivateKey()
{
  if (pkey)
  {
    switch(pkey->type)
    {
      case EVP_PKEY_RSA:
        return new SiRSA(EVP_PKEY_get1_RSA(pkey));

      case EVP_PKEY_DSA:
        return new SiDSA(EVP_PKEY_get1_DSA(pkey));

      case EVP_PKEY_DH:
      default:

        break;
    }
  }
  return NULL;
}
