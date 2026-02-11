plD_red15_gd(PLStream *pls)
{
char r=pls->cmap0[1].r;
char g=pls->cmap0[1].g;
char b=pls->cmap0[1].b;

if (pls->ncol0>15)
   {
    pls->cmap0[1].r=pls->cmap0[15].r;
    pls->cmap0[1].g=pls->cmap0[15].r;
    pls->cmap0[1].b=pls->cmap0[15].r;

    pls->cmap0[15].r=r;
    pls->cmap0[15].g=g;
    pls->cmap0[15].b=b;
   }
}
