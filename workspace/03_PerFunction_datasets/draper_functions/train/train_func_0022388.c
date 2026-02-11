writeRow(QIODevice *dev, unsigned *row, unsigned width, bool alpha) {
    unsigned char *buf = new unsigned char[width * 4];
    unsigned posIn = 0;
    unsigned posOut = 0;

    memset(buf, 0, width * 4);

    unsigned consumed = 0;
    unsigned produced = 0;


    while (posIn < width) {
        if (!encodeRLE(row + posIn, buf + posOut, true, width - posIn, consumed, produced)) {
            delete[] buf;
            return false;
        }
        posIn += consumed;
        posOut += produced;
    }


    if (alpha) {
        posIn = 0;
        while (posIn < width) {
            if (!encodeRLE(row + posIn, buf + posOut, false, width - posIn, consumed, produced)) {
                delete[] buf;
                return false;
            }
            posIn += consumed;
            posOut += produced;
        }
    }

    dev->write((const char*) buf, posOut);
    delete[] buf;
    return true;
}
