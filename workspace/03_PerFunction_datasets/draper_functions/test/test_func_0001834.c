verifyText(KSSLValidation x) {
    switch (x) {

    case KSSLCertificate::Ok:
        return i18n("The certificate is valid.");
    case KSSLCertificate::GetIssuerCertFailed:
        return i18n("Retrieval of the issuer certificate failed. This means the CA's (Certificate Authority) certificate can not be found.");
    case KSSLCertificate::GetCRLFailed:
        return i18n("Retrieval of the CRL (Certificate Revocation List) failed. This means the CA's (Certificate Authority) CRL can not be found.");
    case KSSLCertificate::DecryptCertificateSignatureFailed:
        return i18n("The decryption of the certificate's signature failed. This means it could not even be calculated as opposed to just not matching the expected result.");
    case KSSLCertificate::DecryptCRLSignatureFailed:
        return i18n("The decryption of the CRL's (Certificate Revocation List) signature failed. This means it could not even be calculated as opposed to just not matching the expected result.");
    case KSSLCertificate::DecodeIssuerPublicKeyFailed:
        return i18n("The decoding of the public key of the issuer failed. This means that the CA's (Certificate Authority) certificate can not be used to verify the certificate you wanted to use.");
    case KSSLCertificate::CertificateSignatureFailed:
        return i18n("The certificate's signature is invalid. This means that the certificate can not be verified.");
    case KSSLCertificate::CRLSignatureFailed:
        return i18n("The CRL's (Certificate Revocation List) signature is invalid. This means that the CRL can not be verified.");
    case KSSLCertificate::CertificateNotYetValid:
        return i18n("The certificate is not valid, yet.");
    case KSSLCertificate::CertificateHasExpired:
        return i18n("The certificate is not valid, any more.");
    case KSSLCertificate::CRLNotYetValid:
        return i18n("The CRL (Certificate Revocation List) is not valid, yet.");
    case KSSLCertificate::CRLHasExpired:
        return i18n("The CRL (Certificate Revocation List) is not valid, yet.");
    case KSSLCertificate::CertificateFieldNotBeforeErroneous:
        return i18n("The time format of the certificate's 'notBefore' field is invalid.");
    case KSSLCertificate::CertificateFieldNotAfterErroneous:
        return i18n("The time format of the certificate's 'notAfter' field is invalid.");
    case KSSLCertificate::CRLFieldLastUpdateErroneous:
        return i18n("The time format of the CRL's (Certificate Revocation List) 'lastUpdate' field is invalid.");
    case KSSLCertificate::CRLFieldNextUpdateErroneous:
        return i18n("The time format of the CRL's (Certificate Revocation List) 'nextUpdate' field is invalid.");
    case KSSLCertificate::OutOfMemory:
        return i18n("The OpenSSL process ran out of memory.");
    case KSSLCertificate::SelfSigned:
        return i18n("The certificate is self-signed and not in the list of trusted certificates. If you want to accept this certificate, import it into the list of trusted certificates.");
    case KSSLCertificate::SelfSignedChain:
    case KSSLCertificate::SelfSignedInChain:
        return i18n("The certificate is self-signed. While the trust chain could be built up, the root CA's (Certificate Authority) certificate can not be found.");
    case KSSLCertificate::GetIssuerCertLocallyFailed:
        return i18n("The CA's (Certificate Authority) certificate can not be found. Most likely, your trust chain is broken.");
    case KSSLCertificate::VerifyLeafSignatureFailed:
        return i18n("The certificate can not be verified as it is the only certificate in the trust chain and not self-signed. If you self-sign the certificate, make sure to import it into the list of trusted certificates.");
    case KSSLCertificate::CertificateChainTooLong:
        return i18n("The certificate chain is longer than the maximum depth specified.");
    case KSSLCertificate::Revoked:
    case KSSLCertificate::CertificateRevoked:
        return i18n("The certificate has been revoked.");
    case KSSLCertificate::InvalidCA:
        return i18n("The certificate's CA (Certificate Authority) is invalid.");
    case KSSLCertificate::PathLengthExceeded:
        return i18n("The length of the trust chain exceeded one of the CA's (Certificate Authority) 'pathlength' parameters, making all subsequent signatures invalid.");
    case KSSLCertificate::InvalidPurpose:
        return i18n("The certificate has not been signed for the purpose you tried to use it for. This means the CA (Certificate Authority) does not allow this usage.");
    case KSSLCertificate::Untrusted:
    case KSSLCertificate::CertificateUntrusted:
        return i18n("The root CA (Certificate Authority) is not trusted for the purpose you tried to use this certificate for.");
    case KSSLCertificate::Rejected:
    case KSSLCertificate::CertificateRejected:
        return i18n("The root CA (Certificate Authority) has been marked to be rejected for the purpose you tried to use it for.");
    case KSSLCertificate::IssuerSubjectMismatched:
        return i18n("The certificate's CA (Certificate Authority) does not match the CA name of the certificate.");
    case KSSLCertificate::AuthAndSubjectKeyIDMismatched:
        return i18n("The CA (Certificate Authority) certificate's key ID does not match the key ID in the 'Issuer' section of the certificate you are trying to use.");
    case KSSLCertificate::AuthAndSubjectKeyIDAndNameMismatched:
        return i18n("The CA (Certificate Authority) certificate's key ID and name do not match the key ID and name in the 'Issuer' section of the certificate you are trying to use.");
    case KSSLCertificate::KeyMayNotSignCertificate:
        return i18n("The certificate's CA (Certificate Authority) is not allowed to sign certificates.");
    case KSSLCertificate::ApplicationVerificationFailed:
        return i18n("OpenSSL could not be verified.");


    case KSSLCertificate::SignatureFailed:
        return i18n("The signature test for this certificate failed. This could mean that the signature of this certificate or any in its trust path are invalid, could not be decoded or that the CRL (Certificate Revocation List) could not be verified. If you see this message, please let the author of the software you are using know that he or she should use the new, more specific error messages.");
    case KSSLCertificate::Expired:
        return i18n("This certificate, any in its trust path or its CA's (Certificate Authority) CRL (Certificate Revocation List) is not valid. Any of them could not be valid yet or not valid any more. If you see this message, please let the author of the software you are using know that he or she should use the new, more specific error messages.");


    case KSSLCertificate::ErrorReadingRoot:
    case KSSLCertificate::NoCARoot:
        return i18n("Certificate signing authority root files could not be found so the certificate is not verified.");
    case KSSLCertificate::NoSSL:
        return i18n("SSL support was not found.");
    case KSSLCertificate::PrivateKeyFailed:
        return i18n("Private key test failed.");
    case KSSLCertificate::InvalidHost:
        return i18n("The certificate has not been issued for this host.");
    case KSSLCertificate::Irrelevant:
        return i18n("This certificate is not relevant.");
    default:
    break;
    }

    return i18n("The certificate is invalid.");
}
