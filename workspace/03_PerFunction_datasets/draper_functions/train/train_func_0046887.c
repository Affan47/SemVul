pred4x4_vertical_add_c(uint8_t *pix, const DCTELEM *block, int stride){
    int i;
    pix -= stride;
    for(i=0; i<4; i++){
        uint8_t v = pix[0];
        pix[1*stride]= v += block[0];
        pix[2*stride]= v += block[4];
        pix[3*stride]= v += block[8];
        pix[4*stride]= v += block[12];
        pix++;
        block++;
    }
}
