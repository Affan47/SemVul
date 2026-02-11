dbgHex(const string txt, const char* data, const unsigned int length) {
    if ((doFitDebug) && (this->fitMsgListener != NULL)) {

        stringstream ss;
        ss << txt;
        unsigned int i = 0;
        while (i < length) {
            if ((unsigned char)data[i] < 16) {
                ss << "0";
                ss << hex << (unsigned int)(data[i++] & 0xFF);
            } else {
                ss << hex << (unsigned int)(data[i++] & 0xFF);
            }
            ss << " ";
        }
        dbg(ss.str());
    }
}
