ff_jpegls_reset_coding_parameters(JLSState *s, int reset_all){
    const int basic_t1= 3;
    const int basic_t2= 7;
    const int basic_t3= 21;
    int factor;

    if(s->maxval==0 || reset_all) s->maxval= (1 << s->bpp) - 1;

    if(s->maxval >=128){
        factor= (FFMIN(s->maxval, 4095) + 128)>>8;

        if(s->T1==0     || reset_all)
            s->T1= iso_clip(factor*(basic_t1-2) + 2 + 3*s->near, s->near+1, s->maxval);
        if(s->T2==0     || reset_all)
            s->T2= iso_clip(factor*(basic_t2-3) + 3 + 5*s->near, s->T1, s->maxval);
        if(s->T3==0     || reset_all)
            s->T3= iso_clip(factor*(basic_t3-4) + 4 + 7*s->near, s->T2, s->maxval);
    }else{
        factor= 256 / (s->maxval + 1);

        if(s->T1==0     || reset_all)
            s->T1= iso_clip(FFMAX(2, basic_t1/factor + 3*s->near), s->near+1, s->maxval);
        if(s->T2==0     || reset_all)
            s->T2= iso_clip(FFMAX(3, basic_t2/factor + 5*s->near), s->T1, s->maxval);
        if(s->T3==0     || reset_all)
            s->T3= iso_clip(FFMAX(4, basic_t3/factor + 7*s->near), s->T2, s->maxval);
    }

    if(s->reset==0  || reset_all) s->reset= 64;

}
