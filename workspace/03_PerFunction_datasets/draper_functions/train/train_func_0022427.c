SSL_VersionRangeGetDefault(SSLProtocolVariant protocolVariant,
			   SSLVersionRange *vrange)
{
    if ((protocolVariant != ssl_variant_stream &&
	 protocolVariant != ssl_variant_datagram) || !vrange) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }

    *vrange = *VERSIONS_DEFAULTS(protocolVariant);

    return SECSuccess;
}
