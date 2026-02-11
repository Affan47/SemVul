put_fill_bits (ENC_INST *g)
{
    int iMore;

    put_flush (g);


    iMore = (int)g->wMinBits - 8*(g->pbOutByte - g->pbBufStart);
    if (iMore > 0) {
        iMore = (iMore+7) / 8;
        memset (g->pbOutByte, 0, iMore);
        g->pbOutByte += iMore;
    }
}
