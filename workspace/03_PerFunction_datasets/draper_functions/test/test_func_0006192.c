ff_spatial_idwt_slice(DWTCompose *cs, IDWTELEM *buffer, int width, int height, int stride, int type, int decomposition_count, int y){
    const int support = type==1 ? 3 : 5;
    int level;
    if(type==2) return;

    for(level=decomposition_count-1; level>=0; level--){
        while(cs[level].y <= FFMIN((y>>level)+support, height>>level)){
            switch(type){
            case DWT_97: spatial_compose97i_dy(cs+level, buffer, width>>level, height>>level, stride<<level);
                break;
            case DWT_53: spatial_compose53i_dy(cs+level, buffer, width>>level, height>>level, stride<<level);
                break;
            }
        }
    }
}
