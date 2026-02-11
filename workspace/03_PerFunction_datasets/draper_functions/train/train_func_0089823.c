pdp_imageproc_legalheight(int i)
{

    if (i>0) return  ((((i-1)>>3)+1)<<3);
    return 8;
}
