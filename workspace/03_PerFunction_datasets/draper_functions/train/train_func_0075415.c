read(QImage *outImage)
{
    SGIImage sgi(device());
    return sgi.readImage(*outImage);
}
