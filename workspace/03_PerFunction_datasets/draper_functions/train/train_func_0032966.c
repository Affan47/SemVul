vertical_decompose97iL1(DWTELEM *b0, DWTELEM *b1, DWTELEM *b2, int width){
    int i;

    for(i=0; i<width; i++){
        b1[i] += (W_DM*(b0[i] + b2[i])+W_DO)>>W_DS;
    }
}
