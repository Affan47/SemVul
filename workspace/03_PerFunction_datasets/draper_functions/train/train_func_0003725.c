hasValidNmeaChecksum(const char *data, int size)
{
    int asteriskIndex = -1;
    for (int i = 0; i < size; i++) {
        if (data[i] == '*') {
            asteriskIndex = i;
            break;
        }
    }

    const int CSUM_LEN = 2;
    if (asteriskIndex < 0 || asteriskIndex + CSUM_LEN >= size)
        return false;


    int result = 0;
    for (int i = 1; i < asteriskIndex; i++)
        result ^= data[i];


    QString s;
    s.sprintf("%02x", result);
    return s.toAscii() == QByteArray(&data[asteriskIndex+1], 2);
}
