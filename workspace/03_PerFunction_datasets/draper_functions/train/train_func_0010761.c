integral_init8h( uint16_t *sum, pixel *pix, int stride )
{
    int v = pix[0]+pix[1]+pix[2]+pix[3]+pix[4]+pix[5]+pix[6]+pix[7];
    for( int x = 0; x < stride-8; x++ )
    {
        sum[x] = v + sum[x-stride];
        v += pix[x+8] - pix[x];
    }
}
