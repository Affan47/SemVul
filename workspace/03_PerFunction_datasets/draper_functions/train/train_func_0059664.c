reserve (size_t res_arg)
{
    if (res_arg == OFString_npos) {
        res_arg = 0;
    }
    res_arg++;
    if (this->theCapacity < res_arg) {
        char* newstr = new char[res_arg];
        if (newstr) {
            size_t usedSpace = 0;
            this->theCapacity = res_arg - 1;
            if (this->size() > 0) {
                const size_t len = size();

                OFBitmanipTemplate<char>::copyMem(this->theCString, newstr, len);
                usedSpace = len;
            }
            OFBitmanipTemplate<char>::zeroMem(newstr + usedSpace, res_arg - usedSpace);
            char* oldstr = this->theCString;
            this->theCString = newstr;
            delete[] oldstr;
        } else {
            OFSTRING_MEMORYALLOCERROR(newstr);
        }
    }
}
