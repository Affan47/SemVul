sec_asn1e_which_choice
(
  void *src,
  const SEC_ASN1Template *theTemplate
)
{
  int rv;
  unsigned int which = *(unsigned int *)src;

  for( rv = 1, theTemplate++; theTemplate->kind != 0; rv++, theTemplate++ ) {
    if( which == theTemplate->size ) {
      return rv;
    }
  }

  return 0;
}
