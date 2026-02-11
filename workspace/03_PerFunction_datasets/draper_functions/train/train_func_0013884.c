getMD5DigestFromKDEKey(const QString &k) {
    QString rc;
    int pos = k.lastIndexOf('(');
    if (pos != -1) {
        unsigned int len = k.length();
        if (k.at(len-1) == ')') {
            rc = k.mid(pos+1, len-pos-2);
        }
    }
    return rc;
}
