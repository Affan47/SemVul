readOss(MprSocket *sp, void *buf, ssize len)
{
    MprSslSocket    *osp;
    int             rc, error, retries, i;

    lock(sp);
    osp = (MprSslSocket*) sp->sslSocket;
    mprAssert(osp);

    if (osp->osslStruct == 0) {
        mprAssert(osp->osslStruct);
        unlock(sp);
        return -1;
    }


    retries = 5;
    for (i = 0; i < retries; i++) {
        rc = SSL_read(osp->osslStruct, buf, (int) len);
        if (rc < 0) {
            char    ebuf[MPR_MAX_STRING];
            error = SSL_get_error(osp->osslStruct, rc);
            if (error == SSL_ERROR_WANT_READ || error == SSL_ERROR_WANT_CONNECT || error == SSL_ERROR_WANT_ACCEPT) {
                continue;
            }
            ERR_error_string_n(error, ebuf, sizeof(ebuf) - 1);
            mprLog(4, "SSL_read error %d, %s", error, ebuf);
        }
        break;
    }

#if DEBUG
    if (rc > 0 && !connTraced) {
        X509_NAME   *xSubject;
        X509        *cert;
        char        subject[260], issuer[260], peer[260];

        mprLog(4, "%d: OpenSSL Connected using: \"%s\"", sock, SSL_get_cipher(ssl));

        cert = SSL_get_peer_certificate(ssl);
        if (cert == 0) {
            mprLog(4, "%d: OpenSSL Details: client supplied no certificate", sock);

        } else {
            xSubject = X509_get_subject_name(cert);
            X509_NAME_oneline(xSubject, subject, sizeof(subject) -1);
            X509_NAME_oneline(X509_get_issuer_name(cert), issuer, sizeof(issuer) -1);
            X509_NAME_get_text_by_NID(xSubject, NID_commonName, peer, sizeof(peer) - 1);
            mprLog(4, "%d: OpenSSL Subject %s", sock, subject);
            mprLog(4, "%d: OpenSSL Issuer: %s", sock, issuer);
            mprLog(4, "%d: OpenSSL Peer: %s", sock, peer);
            X509_free(cert);
        }
        connTraced = 1;
    }
#endif

    if (rc <= 0) {
        error = SSL_get_error(osp->osslStruct, rc);
        if (error == SSL_ERROR_WANT_READ) {
            rc = 0;
        } else if (error == SSL_ERROR_WANT_WRITE) {
            mprNap(10);
            rc = 0;
        } else if (error == SSL_ERROR_ZERO_RETURN) {
            sp->flags |= MPR_SOCKET_EOF;
            rc = -1;
        } else if (error == SSL_ERROR_SYSCALL) {
            sp->flags |= MPR_SOCKET_EOF;
            rc = -1;
        } else if (error != SSL_ERROR_ZERO_RETURN) {

            rc = -1;
        }
    } else if (SSL_pending(osp->osslStruct) > 0) {
        sp->flags |= MPR_SOCKET_PENDING;
        mprRecallWaitHandlerByFd(sp->fd);
    }
    unlock(sp);
    return rc;
}
