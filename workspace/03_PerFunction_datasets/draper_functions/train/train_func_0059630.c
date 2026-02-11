pixSizesEqual(PIX  *pix1,
              PIX  *pix2)
{
    PROCNAME("pixSizesEqual");

    if (!pix1 || !pix2)
        return ERROR_INT("pix1 and pix2 not both defined", procName, 0);

    if (pix1 == pix2)
        return 1;

    if ((pixGetWidth(pix1) != pixGetWidth(pix2)) ||
        (pixGetHeight(pix1) != pixGetHeight(pix2)) ||
        (pixGetDepth(pix1) != pixGetDepth(pix2)))
        return 0;
    else
        return 1;
}
