clearRule(const KSslCertificateRule &rule)
{
    clearRule(rule.certificate(), rule.hostName());
}
