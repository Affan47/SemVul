oilPaintConvolve(QImage &src, double radius)
{
    unsigned long count ;
    unsigned long histogram[256];
    unsigned int k;
    int width;
    int x, y, mx, my, sx, sy;
    int mcx, mcy;
    unsigned int *s=0, *q;


    QImage dest(src.width(), src.height(), src.transparent());

    width = getOptimalKernelWidth(radius, 0.5);
    if(src.width() < width){

        return(dest);
    }


    unsigned int **jumpTable = (unsigned int **)src.jumpTable();
    for(y=0; y < dest.height(); ++y){
        sy = y-(width/2);
        q = (unsigned int *)dest.scanLine(y);
        for(x=0; x < dest.width(); ++x){
            count = 0;
            memset(histogram, 0, 256*sizeof(unsigned long));

            sy = y-(width/2);
            for(mcy=0; mcy < width; ++mcy, ++sy){
                my = sy < 0 ? 0 : sy > src.height()-1 ?
                    src.height()-1 : sy;
                sx = x+(-width/2);
                for(mcx=0; mcx < width; ++mcx, ++sx){
                    mx = sx < 0 ? 0 : sx > src.width()-1 ?
                        src.width()-1 : sx;

                    k = intensityValue(jumpTable[my][mx]);
                    if(k > 255){


                        k = 255;
                    }
                    histogram[k]++;
                    if(histogram[k] > count){
                        count = histogram[k];
                        s = jumpTable[my]+mx;
                    }
                }
            }
            *q++ = (*s);
        }
    }

    return(dest);
}
