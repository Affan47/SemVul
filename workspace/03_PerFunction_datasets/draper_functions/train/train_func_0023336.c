SSLv3_MAC_ConstantTime(
    unsigned char *result,
    unsigned int *resultLen,
    unsigned int maxResultLen,
    const SECHashObject *hashObj,
    const unsigned char *secret,
    unsigned int secretLen,
    const unsigned char *header,
    unsigned int headerLen,
    const unsigned char *body,
    unsigned int bodyLen,
    unsigned int bodyTotalLen)
{
  if (!vector && PR_SUCCESS != freebl_RunLoaderOnce())
      return SECFailure;
  return (vector->p_SSLv3_MAC_ConstantTime)(
      result, resultLen, maxResultLen,
      hashObj,
      secret, secretLen,
      header, headerLen,
      body, bodyLen, bodyTotalLen);
}
