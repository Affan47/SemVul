_DrawAngle(IRasterizatedVarying* output, int x1, int y1, int x2, int y2, int x3, int y3, int width, int height, GLDepthBuffer* buffer, linearFunc* func)
{
    int temp;

    if (y1 < y2)
    {
        SWAP(x1, x2);
        SWAP(y1, y2);
    }
    if (y2 < y3)
    {
        SWAP(y2, y3);
        SWAP(x2, x3);
    }
    if (y1 < y2)
    {
        SWAP(x1, x2);
        SWAP(y1, y2);
    }

    float k = (float)(y1-y3)/(float)(x1-x3);
    int xm = (y2-y3)/k + x3;
    _DrawAngle_flat(output, x1, y1, x2, xm, y2, width, height, buffer, func);
    _DrawAngle_flat(output, x3, y3, x2, xm, y2, width, height, buffer, func);
}
