hmacMD5 (const QByteArray &data, const QByteArray &key)
{
    quint8 ipad[64], opad[64];
    QByteArray ret;

    memset (ipad, 0x36, sizeof (ipad));
    memset (opad, 0x5c, sizeof (opad));

    for (int i = key.size() - 1; i >= 0; i--) {
        ipad[i] ^= key[i];
        opad[i] ^= key[i];
    }

    QByteArray content (data.size() + 64, 0);
    memcpy (content.data(), ipad, 64);
    memcpy (content.data() + 64, data.data(), data.size());

    QCryptographicHash md5 (QCryptographicHash::Md5);
    md5.addData (content);
    content.resize (64);
    memcpy (content.data(), opad, 64);
    content += md5.result();

    md5.reset();
    md5.addData (content);

    return md5.result();
}
