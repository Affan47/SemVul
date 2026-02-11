nssUTF8_Size
(
  const NSSUTF8 *s,
  PRStatus *statusOpt
)
{
  PRUint32 sv;

#ifdef NSSDEBUG
  if( (const NSSUTF8 *)NULL == s ) {
    nss_SetError(NSS_ERROR_INVALID_POINTER);
    if( (PRStatus *)NULL != statusOpt ) {
      *statusOpt = PR_FAILURE;
    }
    return 0;
  }
#endif

  sv = PL_strlen((const char *)s) + 1;
#ifdef PEDANTIC
  if( '\0' != ((const char *)s)[ sv-1 ] ) {

    nss_SetError(NSS_ERROR_VALUE_TOO_LARGE);
    if( (PRStatus *)NULL != statusOpt ) {
      *statusOpt = PR_FAILURE;
    }
    return 0;
  }
#endif

  if( (PRStatus *)NULL != statusOpt ) {
    *statusOpt = PR_SUCCESS;
  }

  return sv;
}
