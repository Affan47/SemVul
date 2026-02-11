dumpX509Certificate(X509 *peerCertificate)
{
  if (peerCertificate)
  {
    long certVersion = 0;
    long certSerialNumber = -1;
    OFString certValidNotBefore;
    OFString certValidNotAfter;
    char certSubjectName[1024];
    char certIssuerName[1024];
    const char *certPubKeyType = "unknown";
    int certPubKeyBits = 0;
    certSubjectName[0]= '\0';
    certIssuerName[0]= '\0';
    certVersion = X509_get_version(peerCertificate) +1;
    certSerialNumber = ASN1_INTEGER_get(X509_get_serialNumber(peerCertificate));
    BIO *certValidNotBeforeBIO = BIO_new(BIO_s_mem());
    char *bufptr = NULL;
    if (certValidNotBeforeBIO)
    {
      ASN1_UTCTIME_print(certValidNotBeforeBIO, X509_get_notBefore(peerCertificate));
      BIO_write(certValidNotBeforeBIO,"\0",1);
      BIO_get_mem_data(certValidNotBeforeBIO, OFreinterpret_cast(char *, &bufptr));
      if (bufptr) certValidNotBefore = bufptr;
      BIO_free(certValidNotBeforeBIO);
    }
    bufptr = NULL;
    BIO *certValidNotAfterBIO  = BIO_new(BIO_s_mem());
    if (certValidNotAfterBIO)
    {
      ASN1_UTCTIME_print(certValidNotAfterBIO, X509_get_notAfter(peerCertificate));
      BIO_write(certValidNotAfterBIO,"\0",1);
      BIO_get_mem_data(certValidNotAfterBIO, OFreinterpret_cast(char *, &bufptr));
      if (bufptr) certValidNotAfter = bufptr;
      BIO_free(certValidNotAfterBIO);
    }
    X509_NAME_oneline(X509_get_subject_name(peerCertificate), certSubjectName, 1024);
    X509_NAME_oneline(X509_get_issuer_name(peerCertificate), certIssuerName, 1024);
    EVP_PKEY *pubkey = X509_get_pubkey(peerCertificate);
    if (pubkey)
    {
      switch (EVP_PKEY_type(pubkey->type))
      {
        case EVP_PKEY_RSA:
          certPubKeyType = "RSA";
          break;
        case EVP_PKEY_DSA:
          certPubKeyType = "DSA";
          break;
        case EVP_PKEY_DH:
          certPubKeyType = "DH";
          break;
        default:

          break;
      }
      certPubKeyBits = EVP_PKEY_bits(pubkey);
      EVP_PKEY_free(pubkey);
    }
    OFOStringStream out;
    out << "X.509v" << certVersion << " Certificate" << OFendl
         << "  Subject      : " << certSubjectName << OFendl
         << "  Issued by    : " << certIssuerName << OFendl
         << "  Serial no.   : " << certSerialNumber << OFendl
         << "  Validity     : not before " << certValidNotBefore << ", not after " << certValidNotAfter << OFendl
         << "  Public key   : " << certPubKeyType << ", " << certPubKeyBits << " bits" << OFendl << OFStringStream_ends;
    OFSTRINGSTREAM_GETOFSTRING(out, ret)
    return ret;
  } else {
    return "No X.509 Certificate.";
  }
}
