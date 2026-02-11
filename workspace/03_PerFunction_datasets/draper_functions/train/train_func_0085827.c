deblock_v_chroma_c( pixel *pix, int stride, int alpha, int beta, int8_t *tc0 )
{
    deblock_chroma_c( pix, 2, stride, 2, alpha, beta, tc0 );
}
