ff_faanidct_put(uint8_t *dest, int line_size, DCTELEM block[64]){
    FLOAT temp[64];
    int i;

    emms_c();

    for(i=0; i<64; i++)
        temp[i] = block[i] * prescale[i];

    p8idct(block, temp, NULL,         0, 1, 8, 0);
    p8idct(NULL , temp, dest, line_size, 8, 1, 3);
}
