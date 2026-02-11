ff_spatial_dwt(DWTELEM *buffer, int width, int height, int stride, int type, int decomposition_count){
    int level;

    for(level=0; level<decomposition_count; level++){
        switch(type){
        case DWT_97: spatial_decompose97i(buffer, width>>level, height>>level, stride<<level); break;
        case DWT_53: spatial_decompose53i(buffer, width>>level, height>>level, stride<<level); break;
        }
    }
}
