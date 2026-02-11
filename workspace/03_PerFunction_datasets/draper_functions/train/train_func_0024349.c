plD_gd_optimise(PLStream *pls)
{
png_Dev *dev=(png_Dev *)pls->dev;
int i,j;
char *bbuf;

bbuf=calloc(256,(size_t) 1);
if (bbuf==NULL) plexit("plD_gd_optimise: Out of memory.");

    for(i=0;i<(pls->xlength-1);i++)
       {
        for(j=0;j<(pls->ylength-1);j++)
           {
            bbuf[gdImagePalettePixel(dev->im_out, i, j)]=1;
           }
       }

for (i=0;i<256;i++)
    {
    if (bbuf[i]==0) gdImageColorDeallocate(dev->im_out,i);
    }

free(bbuf);
}
