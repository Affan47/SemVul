setData(size_t size, const unsigned char* data) {
    delete[] fDataBuffer;
    fDataSize = size;
    fDataBuffer = new unsigned char[size];
    memcpy(fDataBuffer, data, size);
}
