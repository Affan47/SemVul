print_chr(unsigned char chr,
               unsigned char *window_chr,
               int *window_start,
               int *window_end,
               double *window_cov,
               int *chr_start_idx) {
    int i;
    char chr_str[64];
         if (chr == CHR_X) { chr_str[0] = 'X'; chr_str[1] = '\0'; }
    else if (chr == CHR_Y) { chr_str[0] = 'Y'; chr_str[1] = '\0'; }
    else if (chr == CHR_M) {
        chr_str[0] = 'M'; chr_str[1] = 'T'; chr_str[2] = '\0';
    } else sprintf(chr_str, "%hhu", chr);

    i = chr_start_idx[chr];
    while (window_chr[i] == chr) {
        printf("%s\t%d\t%d\t%.6g\n",
               chr_str, window_start[i], window_end[i], window_cov[i]);
        i++;
    }
}
