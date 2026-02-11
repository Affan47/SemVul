AddCACert(const Arguments& args) {
  bool newCAStore = false;
  HandleScope scope;

  SecureContext *sc = ObjectWrap::Unwrap<SecureContext>(args.Holder());

  if (args.Length() != 1) {
    return ThrowException(Exception::TypeError(String::New("Bad parameter")));
  }

  if (!sc->ca_store_) {
    sc->ca_store_ = X509_STORE_new();
    newCAStore = true;
  }

  X509* x509 = LoadX509(args[0]);
  if (!x509) return False();

  X509_STORE_add_cert(sc->ca_store_, x509);
  SSL_CTX_add_client_CA(sc->ctx_, x509);

  X509_free(x509);

  if (newCAStore) {
    SSL_CTX_set_cert_store(sc->ctx_, sc->ca_store_);
  }

  return True();
}
