processYUVImage(imageStruct &image)
{

    int h,w,i,length,width,cleanup;
    long srcline,dstline;
    long interlace;

interlace = m_interlace;
if (interlace <= 0){interlace = 1;}
length = image.ysize /interlace;
width = image.xsize * image.csize;
cleanup = image.ysize % interlace;

srcline = 0;
dstline = 0;
if (m_mode == 0){
    for (h =0; h<length;h++){
        for (i = 0; i < interlace - 1; i++){
            dstline += width;
            for (w = 0; w < width;w++){
                image.data[dstline+w] = image.data[srcline+w];
                }
            }
            srcline+= width * interlace;
            dstline += width;
        }
        if (cleanup) {
        for (i = 0; i < cleanup - 1; i++){
            dstline += width;
            for (w = 0; w < width;w++){
                image.data[dstline+w] = image.data[srcline+w];
                }
            }

        }
    }else{
    for (h =0; h<length;h++){
        for (i = 0; i < interlace - 1; i++){
            dstline += width;
            for (w = 0; w < width;w+=2){
                image.data[dstline+w] = 128;
                image.data[dstline+w+1] = 0;
                }
            }
            srcline+= width * interlace;
            dstline += width;
        }
        if (cleanup) {
        for (i = 0; i < cleanup - 1; i++){
            dstline += width;
            for (w = 0; w < width;w+=2){
                image.data[dstline+w] = 128;
                image.data[dstline+w+1] = 0;
                }
            }

        }

    }
}
