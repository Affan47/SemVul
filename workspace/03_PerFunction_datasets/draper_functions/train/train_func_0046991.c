compute_quant_table(int32 *pDst, int16 *pSrc)
{
    int32 q;
    if (m_params.m_quality < 50)
        q = 5000 / m_params.m_quality;
    else
        q = 200 - m_params.m_quality * 2;
    for (int i = 0; i < 64; i++) {
        int32 j = pSrc[i]; j = (j * q + 50L) / 100L;
        pDst[i] = JPGE_MIN(JPGE_MAX(j, 1), 1024/3);
    }

    if (pDst[0] > 8) pDst[0] = (pDst[0]+8*3)/4;
    if (pDst[1] > 24) pDst[1] = (pDst[1]+24)/2;
    if (pDst[2] > 24) pDst[2] = (pDst[2]+24)/2;
}
