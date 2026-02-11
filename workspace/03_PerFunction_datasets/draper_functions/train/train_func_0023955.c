IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "BitmapParams") {
        fPixelSize = tag->getParam("PixelSize", "0").toUint();
        fFlags = tag->getParam("Flags", "0").toUint();
        plString space = tag->getParam("Space", "None");
        for (size_t i=0; i<=kIndexSpace; i++) {
            if (space == kSpaceNames[i])
                fSpace = i;
        }
    } else if (tag->getName() == "Compression") {
        plString cType = tag->getParam("Type", "Uncompressed");
        fCompressionType = kUncompressed;
        for (size_t i=0; i<=kJPEGCompression; i++) {
            if (cType == kCompressionTypeNames[i])
                fCompressionType = i;
        }
        if (fCompressionType == kUncompressed || fCompressionType == kJPEGCompression) {
            plString sType = tag->getParam("SubType", "RGB8888");
            fUncompressedInfo.fType = kRGB8888;
            for (size_t i=0; i<=kAInten88; i++) {
                if (sType == kUncompressedTypeNames[i])
                    fUncompressedInfo.fType = i;
            }
        } else {
            plString sType = tag->getParam("SubType", "Error");
            fDXInfo.fCompressionType = kDXTError;
            for (size_t i=0; i<=kDXT5; i++) {
                if (sType == kCompressedTypeNames[i])
                    fDXInfo.fCompressionType = i;
            }
            fDXInfo.fBlockSize = tag->getParam("BlockSize", "0").toUint();
        }
    } else if (tag->getName() == "ModTime") {
        fLowModTime = tag->getParam("low", "0").toUint();
        fHighModTime = tag->getParam("high", "0").toUint();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
