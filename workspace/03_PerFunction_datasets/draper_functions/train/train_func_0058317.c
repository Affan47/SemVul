camGenerateSinLUT()
{
    int gy;
    double alpha,res;
    FILE *handle=fopen("cam_LUT.c","wt");
    fprintf(handle,"unsigned char camSinLUT[256]={");

    for (gy=0;gy<256;gy++) {
        alpha=atan(gy/256.0);
        res=sin(alpha);
        fprintf(handle,"%d",(int)(res*256+0.5));
        if (gy!=255) fprintf(handle,",");
    }
    fprintf(handle,"};\n");
    fprintf(handle,"unsigned char camCosLUT[256]={");

    for (gy=0;gy<256;gy++) {
        alpha=atan(gy/256.0);
        res=cos(alpha);
        fprintf(handle,"%d",(int)(res*256+0.5)-1);
        if (gy!=255) fprintf(handle,",");
    }
    fprintf(handle,"};\n");
    fclose(handle);
}
