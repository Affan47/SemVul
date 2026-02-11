getEmails(QStringList &to) const {
    to.clear();
#ifdef KSSL_HAVE_SSL
    if (!d->m_cert) {
        return;
    }

    STACK *s = d->kossl->X509_get1_email(d->m_cert);
    if (s) {
        for(int n=0; n < s->num; n++) {
            to.append(d->kossl->sk_value(s,n));
        }
        d->kossl->X509_email_free(s);
    }
#endif
}
