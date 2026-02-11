isTgaType(BasicIo& iIo, bool )
    {

#ifdef EXV_UNICODE_PATH
        std::wstring wpath = iIo.wpath();
        if(   wpath.rfind(EXV_WIDEN(".tga")) != std::wstring::npos
           || wpath.rfind(EXV_WIDEN(".TGA")) != std::wstring::npos) {
            return true;
        }
#else
        std::string path = iIo.path();
        if(   path.rfind(".tga") != std::string::npos
           || path.rfind(".TGA") != std::string::npos) {
            return true;
        }
#endif
        byte buf[26];
        long curPos = iIo.tell();
        iIo.seek(-26, BasicIo::end);
        if (iIo.error() || iIo.eof())
        {
            return false;
        }
        iIo.read(buf, sizeof(buf));
        if (iIo.error())
        {
            return false;
        }

        bool matched = (memcmp(buf + 8, "TRUEVISION-XFILE", 16) == 0);
        iIo.seek(curPos, BasicIo::beg);
        return matched;
    }
}
