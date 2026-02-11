CompressImage(size_t level, void* src, size_t size) {
    const LevelData& lvl = fLevelData[level];

    if (fCompressionType == kDirectXCompression) {
        unsigned char* imgPtr = fImageData + fLevelData[level].fOffset;
        if (fDXInfo.fCompressionType == kDXT1) {
            squish::CompressImage((squish::u8*)src, lvl.fWidth, lvl.fHeight,
                                    imgPtr, squish::kDxt1 | squish::kColourRangeFit);
        } else if (fDXInfo.fCompressionType == kDXT3) {
            squish::CompressImage((squish::u8*)src, lvl.fWidth, lvl.fHeight,
                                    imgPtr, squish::kDxt3 | squish::kColourRangeFit);
        } else if (fDXInfo.fCompressionType == kDXT5) {
            squish::CompressImage((squish::u8*)src, lvl.fWidth, lvl.fHeight,
                                    imgPtr, squish::kDxt5 | squish::kColourRangeFit);
        } else {
            throw hsBadParamException(__FILE__, __LINE__);
        }
    } else {
        throw hsNotImplementedException(__FILE__, __LINE__, "Compression not currently supported for format.");
    }
}
