freePcmBuffer(PcmBuffer * b)
{
    if (b != 0) {
        free(b->ch[0]);
        free(b->ch[1]);
        b->ch[0] = 0;
        b->ch[1] = 0;
        b->n = 0;
        b->u = 0;
    }
}
