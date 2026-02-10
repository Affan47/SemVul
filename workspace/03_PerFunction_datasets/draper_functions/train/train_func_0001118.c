IPrcWrite(pfPrcHelper* prc) {
    plBitmap::IPrcWrite(prc);

    prc->startTag("Metrics");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Height", fHeight);
    prc->writeParam("Stride", fStride);
    prc->writeParam("TotalSize", (unsigned int)fTotalSize);
    prc->writeParam("MipLevels", (unsigned int)fLevelData.getSize());
    prc->endTag(true);

    if (fCompressionType == kJPEGCompression) {
        prc->startTag("JPEG");
        prc->writeParam("ImageRLE", !isImageJPEG());
        prc->writeParam("AlphaRLE", !isAlphaJPEG());
        prc->endTag();

        prc->writeSimpleTag("ImageData");
        if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData)) {
            prc->writeHexStream(fTotalSize, fImageData);
        } else {
            prc->writeComment("Texture data excluded");
        }
        prc->closeTag();

        if (isImageJPEG()) {
            prc->writeSimpleTag("JpegData");
            if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData))
                prc->writeHexStream(fJPEGSize, fJPEGData);
            else
                prc->writeComment("Texture data excluded");
            prc->closeTag();
        }

        if (isAlphaJPEG()) {
            prc->writeSimpleTag("AlphaData");
            if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData))
                prc->writeHexStream(fJAlphaSize, fJAlphaData);
            else
                prc->writeComment("Texture data excluded");
            prc->closeTag();
        }

        prc->closeTag();
    } else {
        prc->writeSimpleTag("DDS");
        prc->writeHexStream(fTotalSize, fImageData);
        prc->closeTag();
    }
}
