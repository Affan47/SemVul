QStringToUnicodeGooString(const QString &s) {
        int len = s.length() * 2 + 2;
        char *cstring = (char *)gmallocn(len, sizeof(char));
        cstring[0] = 0xfe;
        cstring[1] = 0xff;
        for (int i = 0; i < s.length(); ++i)
        {
            cstring[2+i*2] = s.at(i).row();
            cstring[3+i*2] = s.at(i).cell();
        }
        GooString *ret = new GooString(cstring, len);
        gfree(cstring);
        return ret;
    }
