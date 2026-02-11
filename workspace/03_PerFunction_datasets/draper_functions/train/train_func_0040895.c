mask_sequence(int n_windows, unsigned char *filtered_flag,
                   unsigned char *seq1, unsigned char *seq2) {
    int i;
    for (i = 0; i < n_windows; i++) {
        if (filtered_flag[i]) continue;
        if (seq1[i] != seq2[i]) seq1[i] = NORM;
    }
}
