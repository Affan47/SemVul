ParseJingleEncryption(const buzz::XmlElement* content_elem,
                           MediaContentDescription* media,
                           ParseError* error) {
  const buzz::XmlElement* encryption =
          content_elem->FirstNamed(QN_ENCRYPTION);
  if (encryption == NULL) {
      return true;
  }

  media->set_crypto_required(
      GetXmlAttr(encryption, QN_ENCRYPTION_REQUIRED, false));

  for (const buzz::XmlElement* crypto = encryption->FirstNamed(QN_CRYPTO);
       crypto != NULL;
       crypto = crypto->NextNamed(QN_CRYPTO)) {
    CryptoParams params;
    if (!ParseCryptoParams(crypto, &params, error)) {
      return false;
    }
    media->AddCrypto(params);
  }
  return true;
}
