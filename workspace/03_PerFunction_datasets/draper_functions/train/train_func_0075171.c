myIsTextWideChar(const void *b, int len)
    {
#ifdef sun

        if ((((unsigned long)b)%sizeof(wchar_t))!=0) return FALSE;
#endif
        const wchar_t *s=(const wchar_t*)b;


        if (len<(int)sizeof(wchar_t)) return FALSE;


        if (len&1) return FALSE;


        len=mmin(256,len/sizeof(wchar_t));


        if (*((unsigned short*)s) == 0xFFFE) return TRUE;
        if (*((unsigned short*)s) == 0xFEFF) return TRUE;


        int i,stats=0;
        for (i=0; i<len; i++) if (s[i]<=(unsigned short)255) stats++;
        if (stats>len/2) return TRUE;


        for (i=0; i<len; i++) if (!s[i]) return TRUE;

        return FALSE;
    }
