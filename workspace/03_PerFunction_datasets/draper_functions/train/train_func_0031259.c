parse_array(char * line, char ** out, unsigned short ** out_utf16,
       int * out_utf16_len, int utf8, int ln) {
   if (parse_string(line, out, ln)) return 1;
   if (utf8) {
        w_char w[MAXWORDLEN];
        int n = u8_u16(w, MAXWORDLEN, *out);
        if (n > 0) {
            flag_qsort((unsigned short *) w, 0, n);
            *out_utf16 = (unsigned short *) malloc(n * sizeof(unsigned short));
            if (!*out_utf16) return 1;
            memcpy(*out_utf16, w, n * sizeof(unsigned short));
        }
        *out_utf16_len = n;
   }
   return 0;
}
