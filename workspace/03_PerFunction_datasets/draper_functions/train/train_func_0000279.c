blockContents(int block)
{
    if(!openDataFile()) {
        return QList<QChar>();
    }

    const uchar* data = reinterpret_cast<const uchar*>(dataFile.constData());
    const quint32 offsetBegin = qFromLittleEndian<quint32>(data+20);
    const quint32 offsetEnd = qFromLittleEndian<quint32>(data+24);

    int max = ((offsetEnd - offsetBegin) / 4) - 1;

    QList<QChar> res;

    if(block > max)
        return res;

    quint16 unicodeBegin = qFromLittleEndian<quint16>(data + offsetBegin + block*4);
    quint16 unicodeEnd = qFromLittleEndian<quint16>(data + offsetBegin + block*4 + 2);

    while(unicodeBegin < unicodeEnd) {
        res.append(unicodeBegin);
        unicodeBegin++;
    }
    res.append(unicodeBegin);

    return res;
}
