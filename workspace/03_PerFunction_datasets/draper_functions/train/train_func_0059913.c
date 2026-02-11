IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DynTextMapParams") {
        fVisWidth = tag->getParam("VisWidth", "0").toUint();
        fVisHeight = tag->getParam("VisHeight", "0").toUint();
        fHasAlpha = tag->getParam("HasAlpha", "false").toBool();
    } else if (tag->getName() == "InitBuffer") {
        if (tag->getParam("NULL", "false").toBool()) {
            fInitBuffer = NULL;
        } else {
            fInitBufferLen = tag->getContents().getSize();
            fInitBuffer = new unsigned int[fInitBufferLen];
            tag->readHexStream(fInitBufferLen, (unsigned char*)fInitBuffer);
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}
