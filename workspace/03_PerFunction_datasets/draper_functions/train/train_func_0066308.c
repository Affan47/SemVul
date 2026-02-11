store_table(HYuvContext *s, uint8_t *len, uint8_t *buf){
    int i;
    int index= 0;

    for(i=0; i<256;){
        int val= len[i];
        int repeat=0;

        for(; i<256 && len[i]==val && repeat<255; i++)
            repeat++;

        assert(val < 32 && val >0 && repeat<256 && repeat>0);
        if(repeat>7){
            buf[index++]= val;
            buf[index++]= repeat;
        }else{
            buf[index++]= val | (repeat<<5);
        }
    }

    return index;
}
