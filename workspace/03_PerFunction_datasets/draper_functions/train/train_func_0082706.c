isSupportedFormat(QString format) {
    QStringList pList;
    for(int i=0; positiveList[i]; i++) {
        pList.append(QString::fromLatin1(positiveList[i]));
    }

    return pList.contains(format, Qt::CaseInsensitive);
}
