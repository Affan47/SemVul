ApplyToConfig(BaseConfig& ccfg) const {

    if (!credentialString.empty()) {
      ccfg.AddCredential(credentialString);
    }
    else {
      if (!proxyPath.empty())
        ccfg.AddProxy(proxyPath);
      else {
        ccfg.AddCertificate(certificatePath);
        ccfg.AddPrivateKey(keyPath);
      }
    }
    ccfg.AddCADir(caCertificatesDirectory);

    if(!overlayfile.empty())
      ccfg.GetOverlay(overlayfile);
  }
