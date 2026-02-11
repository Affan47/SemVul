getbuf() {
    int p = 0;
    int o = 0;
    do {
        if (inc == 0) inbits = fread(in, 1, BUFSIZE, fin) * 8;
        for (; inc < inbits; inc++) {
            int b = (in[inc / 8] & (1 << (7 - (inc % 8)))) ? 1 : 0;
            int oldp = p;
            p = dec[p].v[b];
            if (p == 0) {
                if (oldp == lastbit) {
                    fclose(fin);
                    fin = NULL;

                    if (dec[lastbit].c[0]) out[o++]  = dec[lastbit].c[1];
                    return o;
                }
                out[o++] = dec[oldp].c[0];
                out[o++] = dec[oldp].c[1];
                if (o == BUFSIZE) return o;
                p = dec[p].v[b];
            }
        }
        inc = 0;
    } while (inbits == BUFSIZE * 8);
    return fail(MSG_FORMAT, filename);
}
