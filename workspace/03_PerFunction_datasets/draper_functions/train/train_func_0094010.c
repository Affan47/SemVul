string_search(const char *s1, int siz1, int len1,
                         const char *s2, int siz2, int len2,
                         int *bi ,
                         int *ci )
{
    int i;

    if (siz2 == 0) {
        *bi = *ci = 0;
        return TRUE;
    }

    if (siz1 == len1) {
        if (siz2 == len2) {

            if (siz1 < siz2) return FALSE;
            if (siz1 < 256 || siz2 >= 256) {

                for (i=0; i<=siz1-siz2; i++) {
                    if (memcmp(s2, s1+i, siz2) == 0) break;
                }
                if (i == siz1-siz2+1) return FALSE;
            } else {
                i = boyer_moore(s1, siz1, s2, siz2);
                if (i < 0) return FALSE;
            }
            *bi = *ci = i;
            return TRUE;
        } else {
            return FALSE;
        }
    }
    if (len1 >= len2) {
        const char *sp = s1;
        for (i=0; i<=len1-len2; i++) {
            if (memcmp(sp, s2, siz2) == 0) {
                *bi = (int)(sp - s1);
                *ci = i;
                return TRUE;
            }
            sp += SCM_CHAR_NFOLLOWS(*sp) + 1;
        }
    }
    return FALSE;
}
