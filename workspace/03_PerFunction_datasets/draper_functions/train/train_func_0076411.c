replicate() {
    KSSLCertChain *x = new KSSLCertChain;
    QList<KSSLCertificate *> ch = getChain();
    x->setChain(ch);
    qDeleteAll(ch);
    return x;
}
