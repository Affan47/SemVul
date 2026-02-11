get_syllable(const char * word, int wlen)
{
    if (cpdmaxsyllable==0) return 0;

    short num=0;

    if (!utf8) {
        for (int i=0; i<wlen; i++) {
            if (strchr(cpdvowels, word[i])) num++;
        }
    } else if (cpdvowels_utf16) {
        w_char w[MAXWORDUTF8LEN];
        int i = u8_u16(w, MAXWORDUTF8LEN, word);
        for (; i > 0; i--) {
            if (flag_bsearch((unsigned short *) cpdvowels_utf16,
                ((unsigned short *) w)[i - 1], cpdvowels_utf16_len)) num++;
        }
    }
    return num;
}
