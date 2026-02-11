slotTLSHandshaken ()
{

  emit debugMessage ( "TLS handshake done, testing certificate validity..." );


  QCA::TLS::IdentityResult identityResult = d->jabberTLS->peerIdentityResult();
  QCA::Validity            validityResult = d->jabberTLS->peerCertificateValidity();

  if ( identityResult == QCA::TLS::Valid && validityResult == QCA::ValidityGood )
  {
    emit debugMessage ( "Identity and certificate valid, continuing." );


    d->jabberTLSHandler->continueAfterHandshake ();
  }
  else
  {
    emit debugMessage ( "Certificate is not valid, asking user what to do next." );


    if ( ignoreTLSWarnings () )
    {
      emit debugMessage ( "We are supposed to ignore TLS warnings, continuing." );
      d->jabberTLSHandler->continueAfterHandshake ();
    }

    emit tlsWarning ( identityResult, validityResult );
  }

}
