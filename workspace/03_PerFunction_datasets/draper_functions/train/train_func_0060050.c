verify_certificate_callback (SSL_CertificateCallbackArg& arg)
      {
        TCertificateCallback cert_cb = this->cert_callback_;
        if (cert_cb)
          {
            cert_cb->handle_certificate_failure (arg);
          }
        return (arg.ignore_error () ? 1 : 0);
      }
