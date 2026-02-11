loadProps_bin_00 (const QString &fpath)
{
    QFile file(fpath);
    if (!file.open(QIODevice::ReadOnly)) {
        return QString::fromLatin1(SPREF"loadProps: cannot read file '%1'")
                      .arg(fpath);
    }
    QByteArray fctmp = file.readAll();
    file.close();
    const char *fc = fctmp.data();
    const int fclen = fctmp.size();


    qlonglong pos = 0;


    QByteArray head(fc, 8);
    pos += 8;
    if (head != "TSPMAP00") goto END_PROP_PARSE;


    int nentries;
    nentries = bin_read_int(fc, fclen, pos);
    if (pos < 0) goto END_PROP_PARSE;


    for (int i = 0; i < nentries; ++i) {


        QList<QByteArray> ekeys;
        int nekeys = bin_read_int(fc, fclen, pos);
        if (pos < 0) goto END_PROP_PARSE;
        for (int j = 0; j < nekeys; ++j) {
            QByteArray ekey = bin_read_string(fc, fclen, pos);
            if (pos < 0) goto END_PROP_PARSE;
            ekeys.append(ekey);
        }


        QHash<QByteArray, QByteArray> props;
        int nprops = bin_read_int(fc, fclen, pos);
        if (pos < 0) goto END_PROP_PARSE;
        for (int j = 0; j < nprops; ++j) {
            QByteArray pkey = bin_read_string(fc, fclen, pos);
            if (pos < 0) goto END_PROP_PARSE;
            QByteArray pval = bin_read_string(fc, fclen, pos);
            if (pos < 0) goto END_PROP_PARSE;
            props[pkey] = pval;
        }


        foreach (const QByteArray &ekey, ekeys) {
            phraseProps[ekey] = props;
        }
    }

    END_PROP_PARSE:

    if (pos < 0) {
        return QString::fromLatin1(SPREF"loadProps: corrupt compiled map '%1'")
                      .arg(fpath);
    }

    return QString();
}
