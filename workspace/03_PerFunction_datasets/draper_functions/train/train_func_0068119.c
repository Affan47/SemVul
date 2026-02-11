get_cert_dn(const std::string& cert_file) {
  std::string dn_str;
  Arc::Credential cert(cert_file, "", "", "");
  dn_str = cert.GetIdentityName();
  return dn_str;
}
