IWriteRawImage(hsStream* S) {
    unsigned char* dataPtr = fImageData;
    if (fPixelSize == 32) {
        for (size_t i=0; i<fLevelData.getSize(); i++) {
            S->writeInts(fLevelData[i].fSize / 4, (uint32_t*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else if (fPixelSize == 16) {
        for (size_t i=0; i<fLevelData.getSize(); i++) {
            S->writeShorts(fLevelData[i].fSize / 2, (uint16_t*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else if (fPixelSize == 8) {
        for (size_t i=0; i<fLevelData.getSize(); i++) {
            S->write(fLevelData[i].fSize, (uint8_t*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else {
        throw hsBadParamException(__FILE__, __LINE__);
    }
}
